#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSTR 256
#define FRAGS  5

int main(int argc, char** argv)
{
  char test_string[MAXSTR+1] = " \tthis\tis\tthe\ttest";
  printf("The test string: '%s'\n",test_string);

  char* the_delim = "\t";
  char* astr;

  astr = strtok(test_string,the_delim);
  for(int i = 0; i < FRAGS; i++)
    {
      //printf("The fragment: '%s'\n",(astr == NULL) ? "NULL" : astr);
      printf("The fragment: '%s'\n",astr);
      astr = strtok(NULL,the_delim);
    }

  return 0;
}
