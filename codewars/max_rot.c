#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int num_of_digits(int n) {
  int retval = log10(n);
  return ++retval;
}

long long maxRot(long long n) {

  return n;
}

void test_maxRot(void) {
  assert(maxRot(5) == 5);
  assert(maxRot(16) == 61);
  assert(maxRot(74) == 74);
  assert(maxRot(55) == 55);
  assert(maxRot(105) == 105);
  assert(maxRot(180) == 810);
  assert(maxRot(38458215) == 85821534);
  assert(maxRot(195881031) == 988103115);
  assert(maxRot(896219342) == 962193428);
  assert(maxRot(69418307) == 94183076);
}

int main(int argc, char** argv) {
  test_maxRot();
  return EXIT_SUCCESS;
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
