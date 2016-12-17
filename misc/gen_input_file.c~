#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

int main(int argc, char** argv)
{
  FILE* fh = NULL;
  char* fn = "wandrers_nachtlied.txt";
  char* fm = "r";
  if (argc > 1)
    fn = argv[1];

  if((fh = fopen(fn,fm)) == NULL)
    {
      printf("Cannot read file: '%s'.\n",fn);
      exit(100);
    }

  char inputline[MAXLINE] = {};
  while ((fgets(inputline,MAXLINE,fh)) != NULL)
    {
      inputline[strlen(inputline)-1] = '\0';
      puts(inputline);
      //printf("%s",inputline);
      inputline[0] = '\0';
    }

  if(fclose(fh) == EOF)
    {
      printf("Cannot close file: '%s'.\n",fn);
      exit(102);
    }

  return 0;
}
