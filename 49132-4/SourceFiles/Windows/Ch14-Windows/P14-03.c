/*	This program demonstrates the use of the exclusive or
	   Written by: 
	   Date: 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (void)
{
//	Local Declarations
	uint16_t  num1 = 0x0257;
	uint16_t  num2 = 0xA463;
	uint16_t  res;

//	Statements
	res = num1 ^ num2;

//	Print results in hexadecimal
	printf ("Input and results in hexadecimal:\n");
	printf ("num1: %#06X\n", num1);
	printf ("num2: %#06X\n", num2);
	printf ("res:  %#06X\n", res);

	return 0;
}	// main

/*	Results:
Input and results in hexadecimal:
num1: 0X0257
num2: 0XA463
res:  0XA634
*/