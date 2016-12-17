#include <stdio.h>

int main(int argc, char** argv)
{
  int i = 1;
  int (*fp)(const char*, ...) = printf; /* commma before ... is optional, 
					   ampersand before printf is optional */

  fp("i == %d\n",i);		/* asterisk before fp is optional */

  return 0;
}
