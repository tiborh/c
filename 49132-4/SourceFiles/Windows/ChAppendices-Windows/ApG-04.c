/*	Demonstate the use of line command
	   Written by:
           Date:
*/
#line 100 "myprogram.c"
#include <stdio.h>

int main (void)
{

//      Statements
	printf ("line %d\n",  __LINE__);
	printf ("file %s\n",  __FILE__);
	printf ("line %d\n",  __LINE__);
	return 0;
} // main

/* Results:
line 106
file myprogram.c
line 108
*/