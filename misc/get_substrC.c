#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256

int get_substr(char *, char *);

int main(int argc, char *argv[])
{
  if (argc < 3)
    {
      printf("Usage: %s str_to_search_in str_to_search_for\n",argv[0]);
      exit(EXIT_FAILURE);
    }

/*   printf("argv[1]: %s\n",argv[1]); */
/*   printf("argv[2]: %s\n",argv[2]); */
  
  if (get_substr(argv[1],argv[2]) == 0)
    printf("<%s> found in %s\n",argv[2],argv[1]);
  else
    printf("<%s> NOT found in %s\n",argv[2],argv[1]);

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
      return(-1);
    }

  str_end--;

  while((str_start+i<=str_end) && (*(str_start+i) != ' ')){
    str_tag[i] = *(str_start+i);
    i++;
  }
  str_tag[i]='\0';
  strcat(str_searched,str2);

  printf("|%s|\n",str_tag);
  printf("strcmp(argv1&2): %d\n",strcmp(str1,str2));
  printf("strcmp: %d\n",strcmp(str_tag,str_searched));

  return strcmp(str_tag,str_searched);
}
