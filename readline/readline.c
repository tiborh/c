//may come useful:
//#define _POSIX_C_SOURCE 200112L
//#define _ISOC99_SOURCE
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
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char** argv)
{
  char *a_line;

  while(NULL != (a_line = readline("Give me a line: "))) {
    printf("Line read in: \"%s\"\n",a_line);
    free(a_line);
  }

  return 0;
}
