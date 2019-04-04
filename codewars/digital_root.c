#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int digital_root(int n) {
  if (n < 0) {
    printf("Only non-negative integers are accepted.\n");
    return EXIT_FAILURE;
  }
  if (n < 10)
    return n;
  int upper = n / 10;
  int lower = n - upper * 10;
  if (n < 100) {
    int sum = upper + lower;
    if (sum > 9)
      return digital_root(sum);
    return(upper + lower);
  }
  if (upper > 9)
    return lower + digital_root(upper);
  
  return EXIT_SUCCESS;
}

int test_digital_root(void) {
  assert(digital_root(-1) == EXIT_FAILURE);
  assert(digital_root(0) == 0);
  assert(digital_root(5) == 5);
  assert(digital_root(16) == 7);
  assert(digital_root(76) == 4);
  assert(digital_root(942) == 6);
  assert(digital_root(132189) == 6);
  assert(digital_root(493193) == 2);
  return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
  test_digital_root();
  return EXIT_SUCCESS;
}
