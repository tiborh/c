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

char* get_query(void)
{
  char tmp_txt[] = "show tables\0";
  char* query_txt = malloc(sizeof(char) * strlen(tmp_txt));
  strcpy(query_txt,tmp_txt);
 
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

void create_select(MYSQL_RES *result)
{
  MYSQL_ROW row;

  //printf("<form method='get' action='show_table_cols' target='_blank'>\n");
  printf("<form action='show_table_cols' target='_blank'>\n");
  printf("\t<select name='table_name'>\n");
  while ((row = mysql_fetch_row(result))) 
    {
      printf("\t\t<option");
      if (!strcmp(row[0],"TR"))
	printf(" selected='selected'");
      printf(" value='%s'>%s</option>\n",row[0],row[0]);
    }
  printf("\t</select>\n");
  printf("\t<input type='submit' value='show table heads' />\n");
  printf("</form>\n");
  
}

int main(int argc, char **argv)
{    
  MYSQL *con;
  MYSQL_RES *result;
  char* query_txt;

  print_head("Tables in DB");

  query_txt = get_query();
  con = init_connection(query_txt);
  result = mysql_store_result(con);
  if (result == NULL) 
    finish_with_error(con);

  create_select(result);
  //print_table(result);

  print_tail();

  mysql_free_result(result);
  mysql_close(con);
  free(query_txt);
  
  exit(0);
}
