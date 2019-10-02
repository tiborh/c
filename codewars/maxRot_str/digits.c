#include "digits.h"

char* first_digit(char *in_str) {
  char* out_str;
  out_str = malloc(2 * sizeof(char));
  out_str[0] = in_str[0];
  out_str[1] = '\0';
  return out_str;
}

char* rest_digits(char *in_str) {
  char *out_str;
  out_str = malloc(strlen(in_str) * sizeof(char));
  int length = strlen(in_str);
  for(int i = 1; i < length; ++i) {
    out_str[i-1] = in_str[i];
  }
  out_str[strlen(in_str)-1] = '\0';
  return out_str;
}

int num_of_rest(long long n) {
  return((int)(log10(n)));
}

int num_of_digits(long long n) {
  return(1+num_of_rest(n));
}

char* unshift_digits(char* fn, char* ln) {
  char *out_str;
  out_str = malloc(strlen(fn)+strlen(ln)+1);
  strcpy(out_str,fn);
  strcat(out_str,ln);
  return(out_str);
}

char* push_digit(char* fn, char* ln) {
  return(unshift_digits(fn,ln));
}

char* first_to_last(char* in_str) {
  if(strlen(in_str) < 2)
    return in_str;
  return(push_digit(rest_digits(in_str),first_digit(in_str)));
}
