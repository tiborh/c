/*	Demonstrate circular nature of unsigned and two's
	complement integer numbers.
	   Written by:
	   Date:
*/
#include <stdio.h>
#include <limits.h>

int main (void)
{
//	Local Definitions
	unsigned short x = USHRT_MAX;
	         short y = SHRT_MAX;

//	Statements
	printf("Maximum unsigned short value:     %u\n", x);
	x++;
	printf("Maximum unsigned short value + 1: %u\n", x);

	printf("Maximum short value:              %d\n", y);
	y++;
	printf("Maximum short value + 1 :         %d\n", y);

	return 0;
}	// main

/*	Results:
Maximum unsigned value:     65535
Maximum unsigned value + 1: 0
Maximum short value:        32767
Maximum short value + 1 :   -32768
*/