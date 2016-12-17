/*	Demonstrate a simple compilation
	   Written by:
	   Date:
*/
#include <stdio.h>
int main (void)
{
//	Local Declarations
	unsigned int num;
	unsigned int res;

//	Statements
	printf ("Enter the power: ");
	scanf  ("%u", &num);
	res = 1 << num;
	printf ("%u\n", res);
	return 0;
}	// main

/*	Results: 
Enter the power: 14
16384
*/