/*	Test driver for rotate left and right.
	   Written by:
	   Date:
*/
#include <stdio.h>
#include <stdint.h>

//	Function Declarations
uint16_t rotate16Left  (uint16_t num , int n);
uint16_t rotate16Right (uint16_t num , int n);

int main (void)
{
//	Local Declaration
	uint16_t num   = 0X2345;

//	Statements
	printf("Original:      %#06X\n", num);
	printf("Rotated Left:  %#06X\n", rotate16Left (num, 4));
	printf("Rotated Right: %#06X\n", rotate16Right(num, 4));
} // main

/*	=================== rotate16Left ===================
	Rotate 16 bit fixed size integer left n bits.
	   Pre  num is a fixed size 16-bit integer
	   Post num rotated n bits left
*/
uint16_t rotate16Right (uint16_t num , int n)
{
	return  ( ( num  << n ) | ( num >> 16 - n ) );
}	// rotate16Right

/*	=================== rotate16Right ==================
	Rotate 16 bit fixed size integer right n bits.
	   Pre  num is a fixed size 16-bit integer
	   Post num rotated n bits left
*/
uint16_t rotate16Left (uint16_t num , int n)
{
	return  ( ( num >> n ) | ( num << 16 - n ) );
}	// rotate16Left

/*	Results:
Original:      0X2345
Rotated Left:  0X5234
Rotated Right: 0X3452
*/