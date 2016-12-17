#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256
#define TAGLENGTH 16

int get_substr(char *, char *);

int main(int argc, char *argv[])
{
  char tag_txt[TAGLENGTH];

  tag_txt[0]='\0';

  if (argc < 2)
    {
      printf("Usage: %s \"str_to_search_in\"\n",argv[0]);
      exit(EXIT_FAILURE);
    }

/*   printf("argv[1]: %s\n",argv[1]); */
  
  if (get_substr(argv[1],tag_txt) == 0)
    printf("'%s' found in '%s'\n",tag_txt,argv[1]);
  else
    printf("No <tag> found in '%s'\n",argv[1]);

  exit(EXIT_SUCCESS);
}

int get_substr(char *str1, char *str2)
{
  char  *str_start, *str_end;
  char str_tag[LINEWIDTH], str_searched[LINEWIDTH+1];
  int i=0;

  str_searched[0]='<';
  str_searched[1]='\0';

  if ((str_start = strchr(str1,'<')) == NULL)
    {
      printf("tagstart not found\n");
      return(-1);
    }
  if ((str_end = strchr(str1,'>')) == NULL)
    {
      printf("tagend not found\n");
      return(-2);
    }

  str_start++;
  str_end--;

  while((str_start+i<=str_end) && (*(str_start+i) != ' ')){
    str_tag[i] = *(str_start+i);
    i++;
  }
  str_tag[i]='\0';
  strcat(str_searched,str2);
  
  printf("|%s|\n",str_tag);
  strcpy(str2,str_tag);

  return 0;
}
