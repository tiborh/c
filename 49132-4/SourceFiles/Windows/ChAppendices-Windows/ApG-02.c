/*	Use of conditional compilation for debugging
	   Written by:
	   Date:
*/
//	Macro to print integer values
#define PRINT_VAL(a) \
	printf ("At line %d--", __LINE__); \
	printf (#a " contains: %d\n", (a))

#define DEBUG 1

#include <stdio.h>

int main (void)
{
//	Declarations
	int x;
//	Statements
x = 1023;

#if DEBUG
    PRINT_VAL (x);
#endif

//	Later in program
for (int i = 0; i < 2; i++)
	{
	x = x * x;                          // Square x
	PRINT_VAL (i); PRINT_VAL(x);
	} // for
 return 0;
} // main

/*	Results:
At line 22--x contains: 1023
At line 29--i contains: 0
At line 29--x contains: 1046529
At line 29--i contains: 1
At line 29--x contains: 6287361
*/