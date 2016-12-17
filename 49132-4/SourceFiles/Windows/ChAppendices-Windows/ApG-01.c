/*	Show the use of pre-defined macros
	   Written by:
	   Date:
*/
#include <stdio.h>

int main (void)
{
//	Statements
	printf ("line %d\n",  __LINE__);
	printf ("file %s\n",  __FILE__);
	printf ("date %s\n",  __DATE__);
	printf ("time %s\n",  __TIME__);
	printf ("ISO compliance %d\n",  __STDC__);
	printf ("line %d\n",  __LINE__);

	return 0;
}	// main

/*	Results:
line 10
file ApG-01.c
date May 23 2005
time 20:36:28
ISO compliance 1
line 15
*/