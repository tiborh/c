/*	Demonstrate the separate compilations--main
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
	res = power2 (num);
	printf ("%u\n", res);
	return 0;
}	// main
