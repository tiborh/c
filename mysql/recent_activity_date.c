#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define BEGINNING "2013-07-01"
#define DEBUG 0
#define TRNUMLENGTH 7

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

char* get_date()
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  char* time_str = malloc(sizeof(char) * strlen("1970-01-01") + 1);
  sprintf(time_str,"%4d-%02d-%02d",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday);
  return(time_str);
}

void print_head(char* title_txt)
{
  printf("%s%c%c\n",
	 "Content-Type:text/html;charset=utf-8",13,10); /* LF & CR */

  printf("<!doctype html>\n");
  printf("<html>\n");

  printf("<head>\n");
  printf("\t<title>%s</title>\n",title_txt);
  printf("</head>\n");

  printf("<body>\n");
  printf("<h3>%s</h3>\n",title_txt);
}

void print_tail()
{
  printf("</body>\n");
  printf("</html>\n");
}

void print_history_form(char* tabbing,char* eriref)
{
  printf("%s<form action='get_history2' target='_blank'>\n",tabbing);
  printf("%s\t<input type='hidden' name='message' value='%s'></input>\n",tabbing,eriref);
  printf("%s\t<input type='submit' value='%s' />\n",tabbing,eriref);
  printf("%s</form>\n",tabbing);
}

char* get_startday(void)
{
  char *startday = malloc(sizeof(char) * 12);
  char *data;
  char *STARTDAY = get_date();

  data = getenv("QUERY_STRING");

  if(data == NULL)
    {
      printf("<p>No data has passed to the script.</p>\n");
    }
  else if(sscanf(data,"startday=%s",startday)!=1)
    {
      printf("<p>No valid data has been passed.</p>\n");
    }

  if (!strcmp(startday,""))
    strcpy(startday,STARTDAY);
  else if (0 > strcmp(startday,BEGINNING))
    strcpy(startday,BEGINNING);

  printf("<p>Start day retrieved: %s</p>\n",startday);

  free(STARTDAY);
  return startday;
}

bool is_eriref(char* sample)
{
  if (strlen(sample)!=7)
    return false;
  if (!isalpha(*sample))
    return false;
  if (!isalpha(*(sample+1)))
    return false;
  for (int i = 2; i < 7; ++i)
    if (!isdigit(*(sample+i)))
      return false;
  bool zeros = true;

  for (int i = 2; i < 7; ++i)
      if (*(sample+i)!='0')
	zeros = false;

  if (zeros == true)
    return false;

  return true;
}

char* get_query(char* startday)
{
  char* query_txt = malloc(sizeof(char) * 2048);

  sprintf(query_txt,"\
select\n\
  TRHISTORY.eriref,\n\
  TR.status as 'status',\n\
  priority as 'prio',\n\
  diddet_complcode as 'diddet',\n\
  answercode as 'acode',\n\
  left(TR.heading,25) as 'truncated heading',\n\
  product,\n\
  product_rstate as 'rstate',\n\
  TRHISTORY.statusexpl,\n\
  TRHISTORY.actionexpl,\n\
  TRHISTORY.phaseexpl,\n\
  eventdate,\n\
  eventtime,\n\
  TRHISTORY.userid,\n\
  TRHISTORY.mhoid,\n\
  datediff(now(),eventdatetime) as 'datediff'\n\
from TRHISTORY\n\
        left join TRANSWER on TRANSWER.eriref=TRHISTORY.eriref\n\
        left join TR on TR.eriref=TRHISTORY.eriref\n\
where str_to_date(eventdate, '%%d %%b %%Y') >= str_to_date('%s','%%Y-%%m-%%d')\n\
group by eriref \n\
order by eriref,eventdatetime desc\
",startday);

  printf("<!--\n%s\n-->\n",query_txt);
 
  return(query_txt);
}

MYSQL *init_connection(char* query_txt)
{
  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, "127.0.0.1", "cgibin", "gingSimi1", 
          "MHEXTDB", 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
  
  if (mysql_query(con, query_txt)) 
  {
      finish_with_error(con);
  }

  return(con);
}

void print_table(MYSQL_RES *result)
{
  MYSQL_ROW row;
  MYSQL_FIELD *field;
  int num_fields = mysql_num_fields(result);
  char eriref[TRNUMLENGTH+1];
  eriref[0] = '\0';
  bool b_is_eriref=false;
  int row_counter = 0;
  int eri_col = -1;

  printf("<table border='1'>\n");
  while ((row = mysql_fetch_row(result))) 
  { 
    printf("<tr>\n");
    for(int i = 0; i < num_fields; i++)
      {
	if (i == 0) 
	  {
	    int col_counter = 0;
	    while((field = mysql_fetch_field(result)))
	      {
		printf("\t<th>%s</th>\n", field->name);
		if(!strcmp(field->name,"eriref"))
		  {
		    eri_col = col_counter;
		    b_is_eriref=true;
		    if (DEBUG)
		      fprintf(stderr,"strcmp %15s\t \"eriref\" == %2d \t(col==%d,\teri==%d)\n",
			      field->name,strcmp(field->name,"eriref"),col_counter,eri_col);
		  }
		++col_counter;
	      }
	    if(b_is_eriref)
	      {
		printf("\t<th>History</th>\n");
		b_is_eriref = false;
	      }
	    printf("</tr>\n");
	    printf("<tr>\n");
	  }
	printf("\t<td");
	printf("%s",!strcmp(row[i],"Finished By")?  " style='color:red'" : "");
	printf(">");
	if (i == eri_col && row[i] && is_eriref(row[i]))
	  {
	    printf("<a href='https://mhweb.ericsson.se/TREditWeb/faces/tredit/tredit.xhtml?eriref=%s'>",row[i]);
	    strcpy(eriref,row[i]);
	  }
	printf("%s", row[i] ? row[i] : "NULL");
	if (i == 0 && row[i])
	  printf("</a>");
	printf("</td>\n");
      }
    printf("\t<td>\n");
    print_history_form("\t\t",eriref);
    printf("\t</td>\n");
    printf("</tr>\n");
    ++row_counter;
  }
  printf("</table>\n");
  printf("<p>Number of data rows: %d</p>\n",row_counter);
}

int main(int argc, char **argv)
{    
  MYSQL *con;
  MYSQL_RES *result;
  char* query_txt;
  char* startday;

  print_head("Recent TR Activities");

  startday = get_startday();
  query_txt = get_query(startday);
  con = init_connection(query_txt);
  result = mysql_store_result(con);
  if (result == NULL) 
    finish_with_error(con);

  print_table(result);

  print_tail();

  mysql_free_result(result);
  mysql_close(con);
  free(startday);
  free(query_txt);
  
  exit(0);
}
