#include <stdio.h>
#include "functions.h"

int main(int argc, char** argv)
{
  long fib_length = process_input(argc,argv);
  long long first_num = 0;
  long long next_num = 1;
  int i = 0;
  for (; i < fib_length && first_num >= 0; i++)
    {
      printf(" %lld",first_num);
      first_num += next_num;
      next_num = first_num - next_num;
    }
  printf("\n");
  if (i < fib_length)
    printf("(only %d has been displayed because variable cannot store larger numbers)\n",i);
  return 0;
}
