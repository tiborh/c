#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
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
  printf("\t<style>\n");
  printf("\t\ttable {\n");
  printf("\t\t\tborder-collapse: collapse;\n");
  printf("\t\t}\n");
  printf("\t\ttable, th, td {\n");
  printf("\t\t\tborder: 1px solid black;\n");
  printf("\t\t}\n");
  printf("\t</style>\n");
  printf("</head>\n");

  printf("<body>\n");
  printf("<h3>%s</h3>\n",title_txt);
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

char* get_query(void)
{
  char *data;
  char *query_txt = malloc(sizeof(char) * 8192);
  char* tmp_raw = malloc(sizeof(char) * 8192);
  char* tmp_str = malloc(sizeof(char) * 8185);
  
  data = getenv("QUERY_STRING");

  //if (DEBUG)  // removed because of segfault
  //  printf("Length of input: %ld\n",strlen(data));

  if(data == NULL)
      printf("<p>No data has passed to the script.</p>\n");
  else if(sscanf(data,"message=%s",tmp_raw)!=1)
      printf("<p>No valid data has been passed.</p>\n");

  msgdecode(tmp_str,tmp_raw);
  free(tmp_raw);

  if (strlen(tmp_str) == 0)
    {
      printf("<p>Nothing in the query field.</p>\n");
      strcat(tmp_str,"* from TRCHANGEORDERDATA");
    }
  if (DEBUG)
    fprintf(stderr,"tmp_str:\n'%s'\n",tmp_str);
  strcat(query_txt,"select ");
  strcat(query_txt,tmp_str);
  free(tmp_str);

  printf("<!--\n%s\n-->\n",query_txt);

  return query_txt;
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
  
  if (mysql_real_connect(con, "localhost", "cgibin", "gingSimi1", 
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
	if (i == 0 && row[i] && is_eriref(row[i]))
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

  print_head("Query Result");

  query_txt = get_query();

  if (DEBUG)
    fprintf(stderr,"query_txt:\n'%s'\n",query_txt);
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
