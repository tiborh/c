#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256
#define DEBUG 0

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
    printf("<%s> found in '%s'\n",argv[2],argv[1]);
  else
    printf("<%s> NOT found in '%s'\n",argv[2],argv[1]);

  exit(EXIT_SUCCESS);
}

int get_substr(char *str1, char *str2)
{
  char  *str_start;
  char str_searched[LINEWIDTH+1];

  str_searched[0]='<';
  str_searched[1]='\0';
  strcat(str_searched,str2);
  strcat(str_searched,">\0");

#if DEBUG == 1
  printf("assembled tag: |%s|\n",str_searched);
#endif

  if((str_start = strstr(str1,str_searched)) == NULL)
    return -1;
  else
    return 0;
}
