#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testio.h"

FILE* open_file_for_write(char* fn)
{
  FILE* fh = malloc(sizeof(FILE));
  char* fm = "w";

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

void write_info(FILE* fh)
{
  for (int i = 0; i < ROWS; i++)
    {
      char a_line[MAXLINE] = {};
      for (int j = 0; j < COLS; j++)
	{
	  char tempdatstr[MAXDATW] = {};
	  int tempdat = 0;
	  tempdat = rand() % MAXNUM;
	  sprintf(tempdatstr,"%d,",tempdat);
	  strcat(a_line,tempdatstr);
	}
      a_line[strlen(a_line)-1] = '\0';
      //puts(a_line);
      fprintf(fh,"%s\n",a_line);
    }
}

int main(int argc, char** argv)
{
  char* fn = (argc > 1) ? argv[1] : "input.txt";
  FILE* fh = open_file_for_write(fn);
  write_info(fh);
  close_file(fh,fn);
  return 0;
}
