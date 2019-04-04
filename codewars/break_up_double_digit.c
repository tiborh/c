#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char** argv) {
  int a = 16;
  int upper = a / 10;
  int lower = a - upper * 10;
  printf("%d can be broken up into %d and %d.\n",a,upper,lower);
  printf("and their sum is: %d\n",upper+lower);
  return EXIT_SUCCESS;
}
