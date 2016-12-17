/*	Demonstrate the bitwise shift-right operator.
	   Written by: 
	   Date: 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//	Function Declaration
void bin16 (uint16_t num, char* bitStr);

int main (void)
{
//	Local Definitions
	uint16_t num  = 0x0040;
	uint16_t res;
	char     bitStr[17] = {0};

//	Statements
	bin16 (num, bitStr);
	printf("Original value:  %s (%#06x)\n", bitStr, num); 

	res =  num >> 1;
	bin16 (res, bitStr);
	printf("Shifted 1 right: %s (%#06x)\n", bitStr, res);

	res =  num >> 2;
	bin16 (res, bitStr);
	printf("Shifted 2 right: %s (%#06x)\n", bitStr, res);

	res = num >> 4;
	bin16 (res, bitStr);
	printf("Shifted 4 right: %s (%#06x)\n", bitStr, res);

	return 0;
}	// main

/*	======================= bin16 =======================
	Convert fixed 16-bit integer to binary digit string.
	   Pre  num contains integral value to be converted
	        bitStr is pointer to variable for bit string
	   Post bit string stored in str
*/
void bin16 (uint16_t num, char* bitStr)
{
//	Statements
	for (int i = 0; i < 16; i++)
	     bitStr[i] = (char) ((num >> 15 - i) & 0X0001) + 48;
	return;
 }	// bin16

/*	Results:
Original value:  0000000001000000 (0x0040)
Shifted 1 right: 0000000000100000 (0x0020)
Shifted 2 right: 0000000000010000 (0x0010)
Shifted 4 right: 0000000000000100 (0x0004)
*/