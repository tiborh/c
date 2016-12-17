#include <stdio.h>

int main(int argc, char** argv)
{
  int octal = 017;
  int hexad = 0x7f;
  printf("octal: 0%o\n",octal);
  printf("hexadecimal: %x\n",hexad);

  long n = 123456789L;		/* specify to avoid doubt */
  float x = 1.0F;               /* specify to avoid doubt */
  long double z = 4.5L;		/* specify to avoid doubt */
  printf("long: %ld\n",n);
  printf("float: %f\n",x);
  printf("long double: %Lf\n",z);

}
