#include "maxRot.h"
#include "digits.h"

long long* rotvals;
int rotvals_index = 0;

void push_rotvals (long long n) {
  if (rotvals_index == ARR_SIZE-1) {
    puts("Buffer overrun. Exiting.");
    exit(EXIT_FAILURE);
  }
  rotvals[rotvals_index++] = n;
}

long long pop_rotvals(void) {
  return rotvals[--rotvals_index];
}

long long maxval(void) {
  long long maxn = 0;

  for(int i=0; i<rotvals_index; ++i)
    if(*(rotvals+i) > maxn)
      maxn=*(rotvals+i);
  
  return maxn;
}

void print_rotvals(void) {
  for(int i = 0; i < rotvals_index; ++i)
    printf(" %lld",*(rotvals+i));
  printf("\n");
}

// sub-rot will require lots of extra functions to be defined. see digit_funcs.lisp

long long get_num(char* first, char* second) {
  char dest[strlen(first)+strlen(second)+1];
  strcpy(dest,first);
  strcat(dest,second);
  long long outnum = 0;
  sscanf(dest,"%lld",&outnum);
  return outnum;
}

void rotter(char* fn, char* ln) {
  push_rotvals(get_num(fn,ln));
  if (strlen(ln) < 2) {
    return;
  }
  ln = first_to_last(ln);
  //push_rotvals(get_num(fn,ln));
  rotter(push_digit(fn,first_digit(ln)),rest_digits(ln));
}

long long maxRot(long long n) {
  rotvals = malloc(ARR_SIZE * sizeof(long long));
  char sn[num_of_digits(n)+1];
  sn[0] = '\0';
  char fn[num_of_digits(n)+1];
  fn[0] = '\0';
  sprintf(sn,"%lld",n);
  rotter(fn,sn);
  //printf("rotvals_index: %d\n",rotvals_index);
  printf("Stored in array: ");
  print_rotvals();
  long long maxn = maxval();
  rotvals_index = 0;
  free(rotvals);
  return maxn;
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
