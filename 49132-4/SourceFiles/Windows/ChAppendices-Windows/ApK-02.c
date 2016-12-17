/*	Show the use of compilation
	   Written by:
	   Date:
*/
#include <stdio.h>

//	Function Declaration
unsigned int power2 (unsigned int exp);

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

unsigned int  power2 (unsigned int exp)
{
//	Statements
	return (1 << exp);
}	// power2

/*	Result: 
Enter the power: 14
16384
*/