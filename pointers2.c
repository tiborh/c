#include <stdio.h>

int min(int* nums, int size)
{
  int* end = nums + size; 	/* one past the end as the outer limit */
  int small = *nums;		/* nums points at first element */
  while (++nums < end)
    if (*nums < small)
      small = *nums;
  return small;
}

int main(int argc, char** argv)
{
  int a[] = {56,34,89,12,9};
  printf("%d\n",min(a,5));
  printf("sizeof 'a' (size of int x length of array): %d\n",sizeof(a));

  return 0;
}
