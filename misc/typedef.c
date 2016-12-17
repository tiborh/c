//may come useful:
//#define _POSIX_C_SOURCE 200112L
#define _ISOC99_SOURCE
//#define __EXTENSIONS__
//#define _GNU_SOURCE
//more in /usr/include/features.h

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//#include <math.h>
//#include <ctype.h>
//#include <stdbool.h>

int main(int argc, char** argv)
{
  typedef struct prog_info {
    char key;
    int val;
  } PROGD;

  PROGD test = {'a',2};
  printf("%c => %d\n",test.key,test.val);

  PROGD test2[] = {{'a',3},{'b',3},{'c',3},{'d',3}};
  for (int i = 0; i < sizeof(test2) / sizeof(test2[0]); ++i)
    printf("%c => %d\n",test2[i].key,test2[i].val);


  return 0;
}
