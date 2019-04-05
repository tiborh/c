#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int num_of_digits(int n) {
  int retval = log10(n);
  return ++retval;
}


int main(int argc, char** argv) {

  printf("10 base log of %d is %lf.\n",99,log10(99));
  int result = log10(99);
  printf("as integer: %d.\n",result);
  assert(num_of_digits(1) == 1);
  assert(num_of_digits(9) == 1);
  assert(num_of_digits(10) == 2);
  assert(num_of_digits(99) == 2);
  
  return EXIT_SUCCESS;
}
