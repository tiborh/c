#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define DAYS 1
#define DEBUG 0

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
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

int get_days(void)
{
  int days = 0;
  char *data;

  data = getenv("QUERY_STRING");

  if(data == NULL)
    {
      printf("<p>No data has passed to the script.</p>\n");
      days = DAYS;
    }
  else if(sscanf(data,"days=%d",&days)!=1)
    {
      printf("<p>No valid data has been passed.</p>\n");
      days = DAYS;
    }
  if (days < 0)
    days = 0;

  printf("<p>Number of days retrieved: %d</p>\n",days);

  return days;
}

char* get_query(int days)
{
  char* query_txt = malloc(sizeof(char) * 2048);
  int trunc = 25;

  char* columns[19][2] = {
    {"TR.eriref","eriref"},
    {"version","ver"},
    {"priority","prio"},
    {"reguser","reg by"},
    {"curruser","owner"},
    {"status","owner"},
    {"diddet_complcode","diddet"},
    {"product","prod nu"},
    {"product_rstate","r-state"}, 
    {"designation","prod name"},
    {"datediff( curdate(), str_to_date(regdate, '%%Y-%%m-%%d') )","reg dys"},
    {"designmho","design MHO"},
    {"datediff( curdate(), str_to_date(mhodate, '%%Y-%%m-%%d') )","mho dys"},
    {"left(heading %d)","heading (trunc)"},
    {"clonedfrom","cloned from"},
    {"clonedto","cloned to"},
    {"mappedfrom", "mapped from"},
    {"mappedto", "mapped to"},
    {"if(troubleref=TR.eriref,'none',troubleref)","dupl of"}
  };

  sprintf(query_txt,"\
select\n\
  TR.eriref,\n\
  version as 'ver',\n\
  priority as 'prio',\n\
  reguser,\n\
  curruser as 'owner',\n\
  status,\n\
  diddet_complcode as 'diddet',\n\
  product,\n\
  product_rstate as 'r-state', designation,\n\
  datediff( curdate(), str_to_date(regdate, '%%Y-%%m-%%d') ) as 'regdays',\n\
  designmho,\n\
  datediff( curdate(), str_to_date(mhodate, '%%Y-%%m-%%d') ) as 'mhodays',\n\
  left(heading, %d) as 'heading (trunc)',\n\
  clonedfrom,clonedto,\n\
  mappedfrom, mappedto,\n\
  if(troubleref=TR.eriref,'none',troubleref) as 'dupl of' \n\
from TR left join TRCLONEFROM on TR.eriref=TRCLONEFROM.eriref\n\
  left join TRCLONETO on TR.eriref=TRCLONETO.eriref\n\
  left join TRMAPPEDFROM on TR.eriref=TRMAPPEDFROM.eriref\n\
  left join TRMAPPEDTO on TR.eriref=TRMAPPEDTO.eriref \n\
where (designmho in ('ceadev','ceamaint') or regmho in ('ceadev', 'ceamaint'))\n\
  and ( datediff( curdate(), str_to_date(regdate, '%%Y-%%m-%%d') ) <= %d\n\
    or datediff( curdate(), str_to_date(mhodate, '%%Y-%%m-%%d') ) <= %d ) \n\
order by datediff( curdate(), str_to_date(regdate, '%%Y-%%m-%%d') ) asc, eriref\
",trunc,days,days);
 
  printf("<!--\n%s\n-->\n",query_txt);

  return(query_txt);
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
  return true;
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

  printf("<table border='1'>\n");
  int row_counter = 0;

  int eri_col = -1;
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
	printf("\t<td>");
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
  char* query_txt;
  int days;

  print_head("New TRs");

  days = get_days();
  query_txt = get_query(days);
  con = init_connection(query_txt);
  result = mysql_store_result(con);
  if (result == NULL) 
    finish_with_error(con);

  print_table(result);

  print_tail();

  mysql_free_result(result);
  mysql_close(con);
  free(query_txt);
  
  exit(0);
}
