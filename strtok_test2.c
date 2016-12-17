#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSTR 256

int main(int argc, char** argv)
{
  char test_string[MAXSTR] = " \tthis\tis\tthe\ttest";
  printf("The test string: '%s'\n",test_string);
  char* the_delim = "\t";
  char* astr;
  char* sptr;

  astr = strtok_r(test_string,the_delim,&sptr);
  do
    {
      printf("The fragment: '%s'\n",astr);
      printf("(Saved: '%s')\n",sptr);
    }while(NULL != (astr = strtok_r(NULL,the_delim,&sptr)));

  return 0;
}
