#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testio.h"

int* parse_line(char* input_line)
{
    int* output = malloc(COLS * sizeof(int));
    char* astr = NULL;
    int i = 0;
    char* the_delim = malloc(2 * sizeof(char));
    sprintf(the_delim,"%c",DATSEP);

    astr = strtok(input_line,the_delim);
    do {
        *(output+i++) = (0 == strcmp(astr,"")) ? 0 : atoi(astr);
    }while(NULL != (astr = strtok(NULL,the_delim)));

    return output;
}

void get_it(FILE* fh)
{
  char lineread[MAXLINE] = {};
  int loopcounter = 0;
  int* parsedline = NULL;

  while(NULL != fgets(lineread,MAXLINE,fh))
  {
      parsedline = parse_line(lineread);
      print_int_arr(parsedline);
      loopcounter++;
  }

  fprintf(stderr,"Loopcounter: %d\n",loopcounter);
}

int processor(char* fn)
{
  FILE* fh = open_file("r",fn);
  get_it(fh);
  close_file(fh,fn);
  return 0;
}
