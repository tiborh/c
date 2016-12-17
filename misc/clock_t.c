#include <stdio.h>
#include <time.h>

int main(int argc, char** argv)
{
  printf("size of clock_t: %d\n",sizeof(clock_t));
  printf("size of     int: %d\n",sizeof(int));
  printf("size of    long: %d\n",sizeof(long));
  return 0;
}
