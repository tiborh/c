//may come useful:
//#define _POSIX_C_SOURCE 200112L
//#define _ISOC99_SOURCE
//#define __EXTENSIONS__
//#define _GNU_SOURCE
//more in /usr/include/features.h

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
  char a = 'a';
  int chars_printed = 0;
  char* b = "Storing value.";
  int width = 10;
  double pi = acos(-1);
  srand(time(NULL));
  int rn = rand() % 1024;

  printf("A char '%c' (%hhd)\n",a,a); /* hh char length, h short int */
  printf("b: \"%s\"%n (%d)\n",b,&chars_printed,chars_printed); /* %n stores length printed so far */
  printf("Stored value: %d\n",chars_printed);		       /* can be seen only after successful printf. */
  printf("String length of string above: %d\n",strlen(b));
  printf("Width set in a further argument: %*d, %.*lf\n",width,chars_printed,width,pi); /* variable width */
  printf("Dec, oct and hex: %d, %#o, %#x\n",rn,rn,rn); /* add leading 0 or 0x */
  printf("padded: %0*d\n",width,rn);		       /* padding with zeros */

  return 0;
}
