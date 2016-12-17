//may come useful:
//#define _POSIX_C_SOURCE 200112L
//#define _ISOC99_SOURCE
//#define __EXTENSIONS__
//#define _GNU_SOURCE
//more in /usr/include/features.h

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
//#include <time.h>
//#include <math.h>
//#include <ctype.h>

int main(int argc, char** argv)
{
  printf("Size of char: %lu\n",sizeof(char));
  printf("Size of あ: %lu\n",sizeof("あ")-1);

  return 0;
}
