/*	Show the use of universal encoding
	   Written by:
	   Date:
*/
#include <stdio.h>

int main (void)
{
// Declarations
	char ch1 = '\u00A2';
	char ch2 = '\U000000A3';

//	Statements
	printf ("Character ch1: %c\n", ch1);
	printf ("Character ch2: %c\n", ch2);

	return 0;
}	// main

/*	Result: 
Character ch1: �
Character ch2: �
*/