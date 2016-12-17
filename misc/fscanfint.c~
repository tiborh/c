#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1024

FILE* open_file(char* fn)
{
  FILE* fh = malloc(sizeof(FILE));
  char* fm = "r";

  if((fh = fopen(fn,fm)) == NULL)
    {
      printf("Cannot read file: '%s'.\n",fn);
      exit(100);
    }

  return fh;
}

void close_file(FILE* fh, char* fn)
{
  if(fclose(fh) == EOF)
    {
      printf("Cannot close file: '%s'.\n",fn);
      exit(102);
    }
}

void do_it(FILE* fh)
{
  char inputline[MAXLINE] = {};
  int scanreturned = 0;
  int loopcounter = 0;
  while ((scanreturned = fscanf(fh,"%s",inputline)) > 0)
    {
      //printf("%d: %s\n",scanreturned,inputline);
      puts(inputline);
      inputline[0] = '\0';
      loopcounter++;
    }
  fprintf(stderr,"Loopcounter: %d\n",loopcounter);
}

int main(int argc, char** argv)
{
  char* fn = (argc > 1) ? argv[1] : "wandrers_nachtlied.txt";
  FILE* fh = open_file(fn);
  do_it(fh);
  close_file(fh,fn);
  return 0;
}
