#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char** argv) {
  int a = 16;
  int b = 9;
  int c = a / b;
  printf("%d // %d == %d\n",a,b,c);
  return EXIT_SUCCESS;
}
