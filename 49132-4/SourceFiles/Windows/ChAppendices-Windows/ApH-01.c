/*	Demonstrate the use of command-line arguments.
	   Written by: 
	   Date: 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
//	Statements 
	printf ("The number of arguments: %d\n", argc);
	printf ("The name of the program: %s\n", argv[0]);

	for (int i = 1; i < argc; i++)
	   printf ("User Value No. %d: %s\n", i, argv[i]);

	return 0;
} // main 
