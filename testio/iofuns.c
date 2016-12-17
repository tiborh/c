#include <stdio.h>
#include <stdlib.h>
#include "testio.h"

FILE* open_file(char* fm,char* fn)
{
  FILE* fh = malloc(sizeof(FILE));

  if((fh = fopen(fn,fm)) == NULL)
    {
      printf("Cannot open file: '%s'.\n",fn);
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

void print_int_arr(int* thearr)
{
    for(int i = 0; i < COLS; i++)
    {
        printf("%d",*(thearr+i));
        putchar((i < COLS-1) ? ',' : '\n');
    }
}


