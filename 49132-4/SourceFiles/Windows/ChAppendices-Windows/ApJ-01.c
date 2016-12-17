/*	Show the use of auto variables
	   Written by:
	   Date:
*/
#include <stdio.h>

int main (void)
{
//	Statements
	for (int i = 1; i <= 3; i++)
	    {
	      int x = 1;
	      x++;
	       printf ("Value of x in iteration %d is: %d\n", i, x);
	    } // for
	return 0;
}	// main

/*	Result:
Value of x in iteration 1 is: 2
Value of x in iteration 2 is: 2
Value of x in iteration 3 is: 2 
*/