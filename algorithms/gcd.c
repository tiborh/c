#include <stdio.h>
#include <assert.h>

/* Using Euclid's algorithm */
int gcd(int x, int y)
{
  if (0 >= x || 0 >= y)
    return 0;
  else if (x < y)
    return gcd(y,x);
  else if (0 == x % y)
    return y;
  else
    return gcd(y, x % y);
}

void run_tests()
{
  assert(0 == gcd(0,2));
  assert(0 == gcd(1,0));
  assert(0 == gcd(0,0));
  assert(0 == gcd(-1,2));
  assert(0 == gcd(1,-2));
  assert(0 == gcd(-1,-2));
  assert(1 == gcd(1,2));
  assert(1 == gcd(12,23));
  assert(12 == gcd(12,24));
  assert(4 == gcd(12,8));
}

int main(int argc, char** argv)
{
  run_tests();
  int x = 0;
  int y = 0;
  char instr[81] = "";
  puts("Greatest common divisor of two integers.");
  puts("Give two integers separated by a single space.");
  while(1)
    {
      if (NULL == fgets(instr,80,stdin))
	break;
      if (2 > sscanf(instr,"%d %d\n",&x,&y))
	break;
      printf("Result: %d\n",gcd(x,y));
    }
  return 0;
}
