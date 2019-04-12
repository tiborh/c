#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int num_of_digits(int n) {
  int retval = log10(n);
  return ++retval;
}

int main(int argc, char** argv) {
  test_maxRot();
  return EXIT_SUCCESS;
}

