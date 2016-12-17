#include <stdio.h>
#include "functions.h"

int main(int argc, char** argv)
{
  printf("testing string input:\n");
  char* test_str = get_string(argc,argv,3);
  printf("test result: '%s'\n",test_str);

  printf("testing integer input:\n");
  int test_int = get_int(argc,argv);
  printf("test integer: '%d'\n",test_int);

  printf("testing long integer input:\n");
  long test_long = get_long(argc,argv);
  printf("test result: '%ld'\n",test_long);

  printf("testing long long integer input:\n");
  long long test_longlong = get_longlong(argc,argv);
  printf("test result: '%lld'\n",test_longlong);

  printf("testing floating point number input:\n");
  float test_float = get_float(argc,argv);
  printf("test result: '%f'\n",test_float);

  printf("testing double precision floating point number input:\n");
  double test_double = get_double(argc,argv);
  printf("test result: '%lf'\n",test_double);

  printf("testint proc_input:\n");
  char* test_args[] = {"1","25"};
  myInput testinput;
  testinput.num_of_args = 2;
  testinput.args = test_args;
  testinput.nu_of_needed = 4;
  testinput.type_of_needed = integer;
  proc_input(testinput);

  return 0;
}
