/*	Demonstrate compilation with two source files.
	   Written by:
	   Date:
*/
#include <stdio.h>
#include "power2.h"

int main (void)
{
//	Local Declarations
	unsigned int num;
	unsigned int res;
//	Statements
	printf ("Enter the power: ");
	scanf  ("%u", &num);
	res = power2 (num);
	printf ("%u\n", res);
	return 0;
}	// main

/*	Result: 
Enter the power: 14
16384
*/