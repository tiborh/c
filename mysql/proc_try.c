#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define DAYS 1
#define DEBUG 0
#define TAGDATA 256
#define INPUT_ITEMS 2
#define DEFKEY "key"
#define DEFVAL "value"

typedef struct input_info {
  char key[TAGDATA+1];
  char value[TAGDATA+1];
} INPUTD;

typedef char KVSTR[2 * TAGDATA + 2];

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

char* get_data()
{
  char *data;

  data = getenv("QUERY_STRING");

  if(data == NULL)
      printf("<p>No data has passed to the script.</p>\n");

  return data;
}

INPUTD proc_item(char *ditem)
{
  INPUTD an_item;

  char* token = strtok(ditem, "=");
  strcpy(an_item.key,token);
  token = strtok(NULL, "=");
  strcpy(an_item.value,(token == NULL) ? "0": token);

  return an_item;
}

KVSTR* get_pairs(char* data)
{
  KVSTR* subdata = malloc(sizeof(KVSTR) * INPUT_ITEMS);
  const KVSTR DEFKV = "key=value";

  char* token = strtok(data, "&");

  for (int i = 0; i < INPUT_ITEMS; ++i)
    {
      if (token)
	strcpy(subdata[i],token);
      else
	strcpy(subdata[i],DEFKV);
      token = strtok(NULL, "&");
    }

  return subdata;
}

INPUTD* proc_data(char *data)
{
  /* presumes that data is not NULL */
  INPUTD* the_input = malloc(sizeof(INPUTD) * INPUT_ITEMS);
  KVSTR* subdata = get_pairs(data);

  for (int i = 0; i < INPUT_ITEMS; ++i)
    {
      INPUTD an_item = proc_item(subdata[i]);
      strcpy(the_input[i].key,an_item.key);
      strcpy(the_input[i].value,an_item.value);
    }

  free(subdata);
  return the_input;
}

INPUTD* set_defaults()
{
  INPUTD *the_input = malloc(sizeof(INPUTD) * INPUT_ITEMS);
  
  printf("<p>set_defaults has been called</p>\n");
  for (int i = 0; i < INPUT_ITEMS; ++i)
    {
      char tmpstr[TAGDATA+1];
      sprintf(tmpstr,"%s%d",DEFKEY,i);
      strcpy(the_input[i].key,tmpstr);
      sprintf(tmpstr,"%s%d",DEFVAL,i);
      strcpy(the_input[i].value,tmpstr);
    }

  return the_input;
}

void print_data(INPUTD* the_input)
{
  for(int i = 0; i < INPUT_ITEMS; ++i)
    printf("<p>%s => %s</p>\n",the_input[i].key,the_input[i].value);
}

int main(int argc, char** argv)
{
  //MYSQL *con;
  //MYSQL_RES *result;
  char *data;
  INPUTD *the_input;

  print_head("Proc Test");
  data = get_data();

  printf("<p>data: '%s'</p>\n",data);

  if (data == NULL)
    {
      printf("<p>Setting defaults...</p>\n");
      the_input = set_defaults();
    }
  else
    the_input = proc_data(data);
  
  print_data(the_input);

  free(the_input);
  print_tail();

  //mysql_free_result(result);
  //mysql_close(con);

  return 0;
}
