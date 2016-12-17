#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  char *test_command = "ls -l";

  printf("the return value of system(\"%s\"): %d.\n",test_command,system(test_command));

  return 0;
}
