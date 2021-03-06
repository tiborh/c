/*	Demonstrate polynomial division.
	   Written by:
	   Date:
*/
#include <stdio.h>
#include <stdint.h>

//	Function Declaration
int degree (uint16_t);

int main (void)
{
//	Local Declaration
	uint16_t dvdn = 0X0227;
	uint16_t dvsr = 0X0009;
	uint16_t qtnt = 0X0000;
	uint16_t rmdr;
	uint16_t q;
	int      dgre;

//	Statements
	printf ("Dividend:  %#06X\n", dvdn);
	printf ("Divisor:   %#06X\n", dvsr);

	rmdr = dvdn;
	while ((dgre = degree (dvdn) - degree (dvsr)) >= 0)
	   {
	    q    = 1 << dgre;
	    rmdr = dvdn ^ (dvsr << degree (q));
	    qtnt = qtnt | q;
	    dvdn = rmdr;
	   } // while

	printf ("Quotient : %#06X\n", qtnt);
	printf ("Remainder: %#06X\n", rmdr);
	return 0;
}	// main

/*	Determine degree of polynomial represened by 
	a fixed-length 16-bit variable.
	    Pre  poly represents a polynomial
	    Post degree returned
*/
int degree (uint16_t  poly)
{
//	Local Declarations
	uint16_t mask = 0X0001;
	uint16_t temp;
	int      pos= -1;

//	Statements
    for (int i = 0; i <16; i++)
	    {
	     temp = poly >> i;
	     if ((temp & mask) == 1)
	          pos = i;
	    } // for
	return pos;
}	// degree

/*	Results:
Dividend:  0X0227
Divisor:   0X0009
Quotient : 0X004D
Remainder: 0X0002
*/