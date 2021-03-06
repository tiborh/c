/*	Demonstrate the calculation of a checksum using one's
	complement arithmetic.
	   Written by:
	   Date:
*/
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main (void)
{
//	Local Declarations
	uint32_t sum      = 0x00000000;
	uint16_t checksum = 0x0000; 

	char*    str      = "ABCDEFGHI";
	int      len;

//	Statements
	len = strlen (str);
	if (len % 2  == 1)
	   // Make the number of characters even
	   len++;

	for (int i = 0; i < len; i += 2)
	    sum = (sum + str[i] * 256 + str[i + 1]);
	
	// Add carries into lower 16 bits
	while (sum >> 16)
	   sum = (sum & 0xffff) + (sum >> 16);

	// Complement
	checksum = ~sum;

	printf ("str:      %s\n",   str);
	printf ("checksum: %#06X\n", checksum);

	return 0;
}	// main

/*	Results:
str:      ABCDEFGHI
checksum: 0XA5EA
*/