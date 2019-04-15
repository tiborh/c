#include "digits.h"

int num_of_rest(long long n) {
  return((int)(log10(n)));
}

int num_of_digits(long long n) {
  return(1+num_of_rest(n));
}

long long expt(long long m, long long e) {
  if (e == 0)
    return 1;
  if (e == 1)
    return m;
  return(m * expt(m,e-1));
}

long long unshift_digits(long long d,long long n) {
  return(expt(10,num_of_digits(n)) * d + n);
}

long long push_digit(long long n, int d) {
  return(n * 10 + d);
}

int first_digit(long long n) {
  return((int)(floor(n / expt(10,num_of_rest(n)))));
}

long long rest_digits(long long n) {
  if(n < 10)
    return 0;
  return(n - first_digit(n) * expt(10,num_of_rest(n)));
}

long long first_to_last(long long n) {
  if(n < 10)
    return n;
  return(push_digit(rest_digits(n),first_digit(n)));
}




