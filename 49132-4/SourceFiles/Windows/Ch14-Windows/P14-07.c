/*	Demonstrate the bitwise shift-left operator.
	   Written by: 
	   Date: 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bin16.c"

int main (void)
{
//	Local Definitions
	uint16_t num  = 0x0031;
	uint16_t res;
	char     bitStr[17] = {0};

//	Statements
	bin16 (num, bitStr);
	printf("Original value: %s (%#06x)\n", bitStr, num);

	res = num << 1;
	bin16 (res, bitStr);
	printf("Shifted 1 left: %s (%#06x)\n", bitStr, res);

	res =  num << 2;
	bin16 (res, bitStr);
	printf("Shifted 2 left: %s (%#06x)\n", bitStr, res);

	res = num << 4;
	bin16 (res, bitStr);
	printf("Shifted 4 left: %s (%#06x)\n", bitStr, res);

	return 0;
}	// main

/*	Results:
Original value: 0000000000110001 (0x0031)
Shifted 1 left: 0000000001100010 (0x0062)
Shifted 2 left: 0000000011000100 (0x00c4)
Shifted 4 left: 0000001100010000 (0x0310)
*/