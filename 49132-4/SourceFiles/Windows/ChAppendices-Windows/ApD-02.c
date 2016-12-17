/*	Demonstate the storage of real numbers.
	   Written by:
	   Date:
*/
#include <stdio.h>

int main (void)
{
//	Local Declaration
	float x = -314.625;
	float y = +314.625;

//	Statements
	printf ("-314.625: %A\n", x);
	printf ("+314.625:  %A\n", y);
	return 0;
} // main

/*	Results: 
-314.625: -0X1.3AA0000000000P+8
+314.625:  0X1.3AA0000000000P+8
*/