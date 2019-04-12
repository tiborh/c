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


/*********************************************************************************
 * Let us begin with an example:
 *
 * Take a number: 56789. Rotate left, you get 67895. (first to last)
 *
 * Keep the first digit in place and rotate left the other digits: 68957. 
 * (second to last)
 *
 * Keep the first two digits in place and rotate the other ones: 68579.
 * (third to last)
 * 
 * Keep the first three digits and rotate left the rest: 68597. Now it is over since 
 * keeping the first four it remains only one digit which rotated is itself.
 * 
 * You have the following sequence of numbers:
 * 
 * 56789 -> 67895 -> 68957 -> 68579 -> 68597
 * 
 * and you must return the greatest: 68957.
 * 
 * Task
 * Write function max_rot(n) which given a positive integer n returns the maximum 
 * number you got doing rotations similar to the above example.
 * 
 * So max_rot (or maxRot or ... depending on the language) is such as:
 * 
 * max_rot(56789) should return 68957
 * 
 * max_rot(38458215) should return 85821534
*********************************************************************************/
