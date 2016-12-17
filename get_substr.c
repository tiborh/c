#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256

void get_substr(char *, char *);

char  *str_start, *str_end;

int main(int argc, char *argv[])
{
  int i=0;
  char str_tag[LINEWIDTH],str_searched[LINEWIDTH+1];

  str_searched[0]='<';
  str_searched[1]='\0';

  if (argc < 3)
    {
      printf("Usage: %s str_to_search_in str_to_search_for\n",argv[0]);
      exit(EXIT_FAILURE);
    }
  str_start=argv[1];
  str_end=argv[2];
  get_substr(argv[1],argv[2]);

  while((str_start+i<=str_end) && (*(str_start+i) != ' ')){
    str_tag[i] = *(str_start+i);
    i++;
  }
  str_tag[i]='\0';
  strcat(str_searched,argv[2]);

  printf("|%s|\n",str_tag);
  printf("strcmp(argv1&2): %d\n",strcmp(argv[1],argv[2]));
  printf("strcmp: %d\n",strcmp(str_tag,str_searched));

  exit(EXIT_SUCCESS);
}

void get_substr(char *str1, char *str2)
{

  if ((str_start = strchr(str1,'<')) == NULL)
    {
      printf("tagstart not found\n");
      exit(1);
    }
  if ((str_end = strchr(str1,'>')) == NULL)
    {
      printf("tagend not found\n");
      exit(1);
    }

  str_end--;

  /*
  for (i=0;i<tag_length;i++)
    the_tag[i]=str1[tag_start+1+i];
  the_tag[i]='\0';
  */

  return;
}
