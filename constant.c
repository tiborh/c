#include <stdio.h>

int main(int argc, char **argv) {
  const int i = 7; 		/* only at compile time, cannot be array index, only in C++, use #define in C */

  printf("const %d\n",i);
  return 0;
}
