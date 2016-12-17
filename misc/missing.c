#include <stdio.h>
#include <limits.h>

int main(int argc, char** argv)
{
  unsigned long n = ULONG_MAX;
  float x = ULONG_MAX;
  double y = ULONG_MAX;
  long double z = ULONG_MAX;
  
  printf("%lu\n%f\n%f\n%Lf\n",n,x,y,z);

  return 0;
}
