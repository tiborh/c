#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define BEGINNING "2013-07-01"
#define DATELENGTH 10
#define DEBUG 0
#define INPUT_ITEMS 2
#define QUERYLENGTH 2048
#define TAGDATA 256
#define TRUNCLENGTH 25

typedef struct input_info {
  char key[TAGDATA+1];
  char value[TAGDATA+1];
} INPUTD;

typedef char KVSTR[2 * TAGDATA + 2];

char* get_data()
{
  char *data = NULL;

  data = getenv("QUERY_STRING");

  if(data == NULL)
      printf("<p>No data has passed to the script.</p>\n");

  return data;
}

bool validate(char* data)
{
    if(data[0] == 's' &&
       data[1] == 't' &&
       data[2] == 'a' &&
       data[3] == 'r' &&
       data[4] == 't' &&
       data[5] == 'd' &&
       data[6] == 'a' &&
       data[7] == 'y' &&
       data[8] == '=' &&
       isdigit(data[9]) &&
       isdigit(data[10]) &&
       isdigit(data[11]) &&
       isdigit(data[12]) &&
       data[13] == '-' &&
       isdigit(data[14]) &&
       isdigit(data[15]) &&
       data[16] == '-' &&
       isdigit(data[17]) &&
       isdigit(data[18]) &&
       data[19] == '&' &&
       data[20] == 'e' &&
       data[21] == 'n' &&
       data[22] == 'd' &&
       data[23] == 'd' &&
       data[24] == 'a' &&
       data[25] == 'y' &&
       data[26] == '=' &&
       isdigit(data[27]) &&
       isdigit(data[28]) &&
       isdigit(data[29]) &&
       isdigit(data[30]) &&
       data[31] == '-' &&
       isdigit(data[32]) &&
       isdigit(data[33]) &&
       data[34] == '-' &&
       isdigit(data[35]) &&
       isdigit(data[36])
       )
        return true;
    else
        return false;
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

void print_data(INPUTD* the_input)
{
  for(int i = 0; i < INPUT_ITEMS; ++i)
    printf("<p>%s => %s</p>\n",the_input[i].key,the_input[i].value);
}

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
  char* time_str = malloc(sizeof(char) * (DATELENGTH + 1));
  sprintf(time_str,"%4d-%02d-%02d",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday);
  return(time_str);
}

char* get_default_data()
{
  const char* first_tag = "startday";
  const char* second_tag = "endday";
  const char* key_val_sep = "=";
  const char* tag_sep = "&";
  char *TDAY = get_date();
  char *data = malloc(sizeof(char) * (strlen(first_tag) + 
				      strlen(second_tag) + 
				      2 * strlen(TDAY) +
				      2 * strlen(key_val_sep) + 
				      strlen(tag_sep) + 1
				      )
		      );
  
  strcpy(data,first_tag);
  strcat(data,key_val_sep);
  strcat(data,TDAY);
  strcat(data,tag_sep);
  strcat(data,second_tag);
  strcat(data,key_val_sep);
  strcat(data,TDAY);

  free(TDAY);

  return data;
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

char* get_dates(INPUTD* the_input)
{
  char *startday = malloc(sizeof(char) * (DATELENGTH + 2));
  char *endday = malloc(sizeof(char) * (DATELENGTH + 2));
  char *dates = malloc(sizeof(char) * (2 * (DATELENGTH + 2) + 1));

  strcpy(startday,the_input[0].value);
  strcpy(endday,the_input[1].value);

  printf("<p>Start day: %s</p>\n",startday);
  printf("<p>End day: %s</p>\n",endday);

  strcpy(dates,startday);
  strcat(dates," ");
  strcat(dates,endday);
  free(startday);
  free(endday);
  return dates;
}

char* get_query(char* the_dates)
{
  char *startday = malloc(sizeof(char) * (DATELENGTH + 2));
  char *endday = malloc(sizeof(char) * (DATELENGTH + 2));
  char* query_txt = malloc(sizeof(char) * QUERYLENGTH);
  int trunc = TRUNCLENGTH;

  sscanf(the_dates,"%s %s",startday,endday);

  sprintf(query_txt,"\
select\n\
  TR.eriref,\n\
--  version as 'ver',\n\
  priority as 'prio',\n\
  reguser,\n\
  curruser as 'owner',\n\
  status,\n\
  statusexpl as 'status explanation',\n\
  diddet_complcode as 'diddet',\n\
  diddet_expllev1 as 'diddet L1 explanation',\n\
  diddet_expllev2 as 'diddet L2 explanation',\n\
  shodet_complcode as 'shodet',\n\
  shodet_expllev1 as 'shodet L1 explanation',\n\
  shodet_expllev2 as 'shodet L2 explanation',\n\
--  marketref,\n\
  customer,\n\
  product,\n\
  product_rstate as 'r-state', designation,\n\
  regdate,\n\
--  datediff( curdate(), str_to_date(regdate, '%%Y-%%m-%%d') ) as 'regdays',\n\
  designmho,\n\
  left(heading, %d) as 'heading (trunc)'\n\
--  clonedfrom,clonedto,\n\
--  mappedfrom, mappedto,\n\
--  if(troubleref=TR.eriref,'none',troubleref) as 'dupl of'\n\
from TR left join TRCLONEFROM on TR.eriref=TRCLONEFROM.eriref\n\
  left join TRCLONETO on TR.eriref=TRCLONETO.eriref\n\
  left join TRMAPPEDFROM on TR.eriref=TRMAPPEDFROM.eriref\n\
  left join TRMAPPEDTO on TR.eriref=TRMAPPEDTO.eriref\n\
  left join TRMEASURE on TR.eriref=TRMEASURE.eriref\n\
where (designmho in ('ceadev','ceamaint') or regmho in ('ceadev', 'ceamaint'))\n\
  and regdate between '%s' and '%s'\n\
order by datediff( curdate(), str_to_date(regdate, '%%Y-%%m-%%d') ) desc, eriref\n\
",trunc,startday,endday);
 
  printf("<!--\n%s\n-->\n",query_txt);
  free(startday);
  free(endday);

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
  MYSQL *con = NULL;
  MYSQL_RES *result = NULL;
  char* data = NULL;
  char* query_txt = NULL;
  char* the_dates = NULL;
  INPUTD *the_input = NULL;
  char* const_string = "startday=2015-06-01&endday=2015-06-30";
  char* test_string = malloc(sizeof(char) * (strlen(const_string) + 1));

  print_head("TRs Registered (Between)");
  data = get_data();
  if (data == NULL || !validate(data))
    {
      printf("<p>Invalid input data %s</p>\n",(DEBUG) ? data : "has been passed to the script");
      data = get_default_data();
    }
  if (DEBUG)
    {
      strcpy(test_string,const_string);
      data = test_string;
    }
  the_input = proc_data(data);
  //puts("<p>Still alive.</p>\n");
  if (DEBUG)
    print_data(the_input);
  the_dates = get_dates(the_input);
  free(the_input);
  query_txt = get_query(the_dates);
  free(the_dates);

  if (query_txt != NULL)
    {
      con = init_connection(query_txt);
      if (con != NULL)
	{
	  result = mysql_store_result(con);
	  if (result == NULL) 
	    finish_with_error(con);
	  else
	    {
	      print_table(result);
	      mysql_free_result(result);
	    }
	  mysql_close(con);
	}
      free(query_txt);
    }
  print_tail();

  if (data != NULL)
    free(data);

  return 0;
}
