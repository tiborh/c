#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testio.h"

char* genpattern()
{
    char tempstr[8];
    sprintf(tempstr,"%%d%c",DATSEP);
    //char* endstr = " %*c";
    char* endstr = "";
    char* the_pattern = malloc((strlen(tempstr) * COLS + strlen(endstr) + 1)*sizeof(char));
    *the_pattern = '\0';
    for (int i = 0; i < COLS; i++)
        strcat(the_pattern,tempstr);
    the_pattern[strlen(the_pattern)-1] = '\0';
    strcpy(tempstr,endstr);
    strcat(the_pattern,tempstr);

    return the_pattern;
}

void do_it(FILE* fh)
{
  int inputarray[COLS] = {};
  int scanreturned = 0;
  int loopcounter = 0;
  char* rowpattern = genpattern();
  while (COLS == (scanreturned = fscanf(fh,
                                        rowpattern,
                                        &inputarray[0],
                                        &inputarray[1],
                                        &inputarray[2],
                                        &inputarray[3],
                                        &inputarray[4])))
    {
      //printf("%d: %s\n",scanreturned,inputline);
      print_int_arr(inputarray);
      loopcounter++;
    }
  fprintf(stderr,"Loopcounter: %d\n",loopcounter);
}

int fscanf_processor(char* fn)
{
  FILE* fh = open_file("r",fn);
  do_it(fh);
  close_file(fh,fn);
  return 0;
}
