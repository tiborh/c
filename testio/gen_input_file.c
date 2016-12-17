#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "testio.h"

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

int writer(char* fn)
{
  srand(time(NULL));
  FILE* fh = open_file("w",fn);
  write_info(fh);
  close_file(fh,fn);
  return 0;
}
