#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 256
#define DEBUG 0

int str_prepend(char *, char *);

int main(int argc, char **argv)
{
  char str_prepended[LINEWIDTH+1];

  if (argc < 3)
    {
      printf("Usage: %s str_to_prepend_to str_to_prepend\n",argv[0]);
      exit(EXIT_FAILURE);
    }

  printf("first argument: '%s'\n",argv[1]);
  strcpy(str_prepended,argv[1]);

  str_prepend(str_prepended,argv[2]);
  printf("The new string: %s",str_prepended);
  
  exit(EXIT_SUCCESS);
}

int str_prepend(char *str_into, char *str_which)
{
  char strtmp[LINEWIDTH];

  strtmp[0]='\0';
  strcpy(strtmp,str_into);
  strcpy(str_into,str_which);
  strcat(str_into,strtmp);

  return 0;
}
