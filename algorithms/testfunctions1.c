#include <stdio.h>
#include "functions.h"

int main(int argc, char** argv)
{
  //printf("testint get_string:\n");
  //printf("the result: %s\n",get_string(argc,argv,3));

  printf("testint proc_input:\n");
  char* test_args[] = {"progname","1","25"};
  myInput testinput;
  testinput.num_of_args = 3;
  testinput.args = test_args;
  testinput.nu_of_needed = 4;
  testinput.type_of_needed = integer;
  printf("The result: '%s'\n",proc_input(testinput));

  return 0;
}
