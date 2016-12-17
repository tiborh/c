#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testio/testio.h"

int main(int argc, char** argv)
{
  char tempstr[8];
  sprintf(tempstr,"%%d%c",DATSEP);
  char* endstr = " %*c";
  char* the_pattern = malloc((strlen(tempstr) * COLS + strlen(endstr) + 1)*sizeof(char));
  *the_pattern = '\0';
  for (int i = 0; i < COLS; i++)
    strcat(the_pattern,tempstr);
  the_pattern[strlen(the_pattern)-1] = '\0';
  strcpy(tempstr,endstr);
  strcat(the_pattern,tempstr);

  printf("length of pattern: %d\n",strlen(the_pattern));
  printf("Calculation (tempstr(%d) * COLS(%d) + endstr(%d) + 1) * sizeof(char)(%d) == %d\n",
	 strlen(tempstr),
	 COLS,
	 strlen(endstr),
	 sizeof(char),
	 (strlen(tempstr) * COLS + strlen(endstr) + 1)*sizeof(char)
	 );
  puts(the_pattern);
  
  int intarr[5] = {};
  char* sample_input = "12,23,34,45,56\n";
  int result = sscanf(sample_input,the_pattern,&intarr[0],&intarr[1],&intarr[2],&intarr[3],&intarr[4]);
  //int result = sscanf(sample_input,"%d,%d,%d,%d,%d %*c",&intarr[0],&intarr[1],&intarr[2],&intarr[3],&intarr[4]);
  printf("Scan Result == %d\n",result); 

  return 0;
}
