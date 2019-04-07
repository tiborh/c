#include <stdio.h>
#include <stdlib.h>

long long rotvals[100] = {};
int rotvals_index = 0;

void push_rotvals (long long n) {
  if (rotvals_index == 99) {
    printf("Buffer overrun. Exiting.\n");
    exit(EXIT_FAILURE);
  }
  rotvals[rotvals_index++] = n;
}

long long pop_rotvals(void) {
  return rotvals[--rotvals_index];
}

// sub-rot will require lots of extra functions to be defined. see digit_funcs.lisp

long long maxRot(long long n) {
  push_rotvals(n);
  if (n < 10)
    return n;
  
}
