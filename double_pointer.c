#include <stdio.h>

int main(int argc, char** argv)
{
  int i = 2;
  int* pi = &i;
  int** ppi = &pi;

  printf("The double pointer **ppi points to %d\n",**ppi);

  return 0;
}
