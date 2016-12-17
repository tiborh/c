#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define DEBUG 0
#define MAXNUM 100
#define TRNUMLENGTH 7
#define INPUTSIZE (sizeof(char) * MAXNUM * (TRNUMLENGTH * 2))

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
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
}

void print_tail()
{
  printf("</body>\n");
  printf("</html>\n");
}

void msgdecode(char *dst, const char *src)
{
  char a, b;
  while (*src) {
    if (*src == '+')
      {
	*dst = ' ';
	++src;
	++dst;
      }
    else if ((*src == '%') &&
	((a = src[1]) && (b = src[2])) &&
	(isxdigit(a) && isxdigit(b))) {
      if (a >= 'a')
	a -= 'a'-'A';
      if (a >= 'A')
	a -= ('A' - 10);
      else
	a -= '0';
      if (b >= 'a')
	b -= 'a'-'A';
      if (b >= 'A')
	b -= ('A' - 10);
      else
	b -= '0';
      *dst++ = 16*a+b;
      src+=3;
    } else {
      *dst++ = *src++;
    }
  }
  *dst++ = '\0';
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

char* tr_number_parser(char *inputstr)
{
  char* collector = malloc(sizeof(char*) * strlen(inputstr) + 1);
  int lettercount = 0;
  char lettercollect[TRNUMLENGTH + 1];
  char* separator = " ";
  collector[0] = '\0';
  lettercollect[0] = '\0';

  if (DEBUG)
    {
      printf("<p>inputstr in tr_number_parser: '%s'</p>\n",inputstr);
      printf("<p>length of input string: %ld</p>\n",strlen(inputstr));
    }
  for(int i = 0; i < strlen(inputstr); ++i)
    {
      if (DEBUG == 2)
	putchar(inputstr[i]);
      if (!isalnum(inputstr[i]))
	{
	  lettercount = 0;
	  lettercollect[0] = '\0';
	  if (DEBUG == 2)
	    puts(":(not alpha or num)");
	  continue;
	}
      lettercollect[lettercount] = inputstr[i];
      lettercollect[lettercount+1] = '\0';
      ++lettercount;
      if (DEBUG == 2)
	{
	  printf("(collected: %s)",lettercollect);
	  putchar('\n');
	}
      if(strlen(lettercollect) == 7)
	{
	  if(is_eriref(lettercollect))
	    {
	      if(strlen(collector) != 0)
		strcat(collector,separator);
	      strcat(collector,lettercollect);
	      if (DEBUG)
		printf("<p>(%d:) collector: '%s'</p>\n<p>lettercollect: '%s'</p>\n",i,collector,lettercollect);
	    }
	  lettercollect[0] = '\0';
	  lettercount = 0;
	  continue;
	}
    }
  if (DEBUG)
      printf("<p>Collector: '%s'</p>\n",collector);

  return collector;
}

char* embed_trnumbers(char* erirefs)
{
  char* outstring = malloc(strlen(erirefs) * sizeof(char) * 2);
  /* 1 comma, 1 space, 2 quotes */
  char* separator = ", ";
  char quote = '\'';
 
  if (DEBUG)
    printf("<p>erirefs in embed_trnumbers: '%s'</p>\n",erirefs);
 
  outstring[0] = '\0';

  const char s[2] = " ";
   char *token;
   
   /* get the first token */
   token = strtok(erirefs, s);
   
   /* walk through other tokens */
   while( token != NULL ) 
   {
      char tmpstr[TRNUMLENGTH + 3];
      sprintf(tmpstr,"%c%s%c",quote,token,quote);
      strcat(outstring,tmpstr);

      if (DEBUG)
	printf("<p>tmpstr: %s</p>\n",tmpstr);
    
      token = strtok(NULL, s);
      if (token != NULL)
	strcat(outstring,separator);
   }

  return outstring;
}

char* get_tr_numbers()
{
  char *data;
  char* tmp_raw = malloc(INPUTSIZE + 1);
  char* tmp_str = malloc(INPUTSIZE + 1);
  char* tr_nums = NULL;

  data = getenv("QUERY_STRING");

  if(data == NULL)
      printf("<p>No data has passed to the script.</p>\n");
  else if(sscanf(data,"message=%s",tmp_raw)!=1)
      printf("<p>No valid data has been passed.</p>\n");

  msgdecode(tmp_str,tmp_raw);
  free(tmp_raw);

  if (strlen(tmp_str) == 0)
    {
      printf("<p>Nothing in the query field.</p>\n");
      print_tail();
      exit(1);
    }
  else
    {
      tr_nums = tr_number_parser(tmp_str);
      free(tmp_str);
      //tmp_str = embed_trnumbers(tr_nums);
      //free(tr_nums);
    }

  return tr_nums;
}

char* get_query(char* erirefs)
{
  char *query_txt = malloc(INPUTSIZE + 1);
  int trunc = 25;
  
  sprintf(query_txt,"\
select\n\
  TRHISTORY.eriref,\n\
  TR.status as 'status',\n\
  priority as 'prio',\n\
  diddet_complcode as 'diddet',\n\
  answercode as 'acode',\n\
  left(TR.heading,%d) as 'truncated heading',\n\
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
where TRHISTORY.eriref in (%s)\n\
order by TRHISTORY.eriref,eventdatetime desc\
",trunc,erirefs);

  printf("<!--\n%s\n-->\n",query_txt);
 
  return(query_txt);
}

void print_table(MYSQL_RES *result,char *title_txt)
{
  MYSQL_ROW row;
  MYSQL_FIELD *field;
  int num_fields = mysql_num_fields(result);
  int row_counter = 0;
  int eri_col = -1;

  printf("<h3>%s</h3>\n",title_txt);
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
		    if (DEBUG)
		      fprintf(stderr,"strcmp %15s\t \"eriref\" == %2d \t(col==%d,\teri==%d)\n",
			      field->name,strcmp(field->name,"eriref"),col_counter,eri_col);
		  }
		++col_counter;
	      }
	    printf("</tr>\n");
	    printf("<tr>\n");
	  }
	printf("\t<td");
	printf("%s",!strcmp(row[i],"Finished By")?  " style='color:red'" : "");
	printf(">");
	if (i == eri_col && row[i] && is_eriref(row[i]))
	  printf("<a href='https://mhweb.ericsson.se/TREditWeb/faces/tredit/tredit.xhtml?eriref=%s'>",row[i]);
	printf("%s", row[i] ? row[i] : "NULL");
	if (i == 0 && row[i])
	  printf("</a>");
	printf("</td>\n");
      }
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
  char* query_txt = malloc(sizeof(char) * 8192);
  char* tr_nums;
  char* embedded_tr_nums = NULL;
  char* title_txt = "TR History";
  char* head_txt;
  char* sep = ": ";

  print_head(title_txt);

  tr_nums = get_tr_numbers();
  embedded_tr_nums = embed_trnumbers(tr_nums);
  free(tr_nums);
  query_txt = get_query(embedded_tr_nums);
  con = init_connection(query_txt);
  result = mysql_store_result(con);
  if (result == NULL) 
    finish_with_error(con);

  head_txt = malloc(sizeof(char) * (strlen(title_txt) + strlen(embedded_tr_nums) + strlen(sep) + 1));
  strcpy(head_txt,title_txt);
  strcat(head_txt,sep);
  strcat(head_txt,embedded_tr_nums);
  if (DEBUG)
    printf("<p>embedded_tr_nums: %s</p>\n",embedded_tr_nums);
  print_table(result,head_txt);
  free(embedded_tr_nums);

  print_tail();

  mysql_free_result(result);
  mysql_close(con);
  free(query_txt);
  
  exit(0);
}
