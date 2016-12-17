#include <stdio.h>
#include <stdlib.h>

void printarray(int* a, int length)
{
  for(int i = 0; i < length; i++)
    printf("%d: %d\n",i,*(a+i));
}

int main(int argc, char** argv)
{
  int an_array[] = {1,2,3,4,5,6,7};
  int* ptr_array = an_array;
  printf("%d\n",*(ptr_array+3));
  printf("%d\n",ptr_array[3]);
  printf("%d\n",3[ptr_array]);
  int length = 5;
  ptr_array = calloc(length,sizeof(int));
  printarray(ptr_array,length);

  return 0;
}
