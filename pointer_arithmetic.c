#include <stdio.h>
#include <stddef.h>

int main(int argc, char** argv)
{
  float a[] = {1.0,2.0,3.0};
  float *p = &a[0];

  puts("The sample array:");
  printf("%f %f %f\n",a[0],a[1],a[2]);
  printf("sizeof(float) == %u\n",sizeof(float));
  printf("p == %p, *p == %f\n",p,*p);
  puts("After adding 2 to the pointer.");
  p+=2;
  printf("p == %p, *p == %f\n",p,*p);

  ptrdiff_t diff;
  puts("After subtracting 'a' from 'p':");
  diff = p - a;
  printf("diff == %ld\n",(long)diff);
  puts("After subtracting (char*)'a' from (char*)'p':");
  diff = (char*)p - (char*)a;
  printf("diff == %ld\n",(long)diff);

  return 0;
}
