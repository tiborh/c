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
