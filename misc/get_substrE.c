#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256
#define DEBUG 1

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

int get_strfromtag(char *str1, char *str2)
{
  
  return 0;
}

int get_substr(char *str1, char *str2)
{
  char  *str_start, *str_end;
  char str_searched[LINEWIDTH+1];
  char strtmp[LINEWIDTH+1];
  int i=0;

  strtmp[0]='\0';
  str_searched[0]='<';
  str_searched[1]='\0';
  strcat(str_searched,str2);
  strcat(str_searched,"\0");

  if((str_start = strstr(str1,str_searched)) == NULL)
    return -1;
  if((str_start = strchr(str_start,' ')) == NULL)
    return -2;
  if ((str_end = strchr(str_start,'>')) == NULL)
    return -3;

  do{
    strtmp[i]=*(str_start+i);
    i++;
  }while((str_start+i) != str_end);
  strtmp[i]=*str_end;
  strtmp[i+1]='\0';

  strcat(str_searched,strtmp);
  /*strcat(str_searched,">\0");*/

#if DEBUG == 1
  printf("str_end: %c\n",*str_end);
  printf("assembled tag: |%s|\n",str_searched);
#endif

    return 0;
}
