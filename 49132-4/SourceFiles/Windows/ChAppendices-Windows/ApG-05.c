/*	Show the use of error directive
	   Written by:
	   Date:
*/
#define TRUE 1

#if defined (TRUE) && !defined (FALSE)
	#error You need to defined FALSE too.
#elif defined (FALSE) && !defined (TRUE)
	#error You need to defined TRUE too.
#endif

#include <stdio.h>
int main (void)
{
//	Statements
	printf ("Just a test\n");
	return 0;
}	// main

/*	Results:
Error   : preprocessor #error directive
ApG-04.c line 8    #error You need to defined FALSE too. 
*/