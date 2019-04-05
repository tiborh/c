#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int num_of_digits(int n) {
  int retval = log10(n);
  return ++retval;
}

int char_to_num(char c) {
  char char_str[2];
  sprintf(char_str,"%c",c);
  return atoi(char_str);
}

int digital_root_common(int n) {
  int num_of_d = num_of_digits(n);
  char num_str[n+1];
  sprintf(num_str,"%d",n);
  int sum = 0;
  for(int i = 0; i < num_of_d; ++i)
    sum += char_to_num(num_str[i]);
  printf("from %d to %d\n",n,sum);
  return sum;
}

int digital_root_iter(int n) {
  while(n > 9)
    n = digital_root_common(n);
  return n;
}
  
int digital_root_recur(int n) {
  if (n < 10)
    return n;
  n = digital_root_common(n);
  return digital_root_recur(n);
}

int digital_root_recur2(int n) {
  int tenth = n / 10;
  if (tenth == 0)
    return n;
  int last_digit = n - tenth * 10;
  return digital_root_recur2(digital_root_recur2(tenth) + last_digit);
}

int digital_root(int n) {
  if (n < 0) {
    printf("Only non-negative integers are accepted.\n");
    return EXIT_FAILURE;
  }

  // return digital_root_iter(n);
  // return digital_root_recur(n);
  return digital_root_recur2(n);
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
