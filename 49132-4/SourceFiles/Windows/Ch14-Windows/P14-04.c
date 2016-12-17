/*	Demonstrate use of one�s complement
	   Written by: 
	   Date: 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (void)
{
//	Local Declarations
	uint16_t  num = 0x0257;
	uint16_t  res;

//	Statements
	res = ~num;

//	Print results in hexadecimal
	printf ("Input and results in hexadecimal:\n");
	printf ("num: %#06X\n", num);
	printf ("res: %#06X\n", res);

	return 0;
}	// main

/*	Results:
Input and results in hexadecimal:
num: 0X0257
res: 0XFDA8
*/