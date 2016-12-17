/*	Show the use of static variable with file  scope
	   Written by:
	   Date:
*/
#include <stdio.h>

//	Function Declaration
void fun (void);

static int x = 1;

int main (void)
{
//	Statements
	for (int i = 1; i <= 3; i++)
	     x++;
	printf ("Value of x in main is: %d\n", x);
	fun();
	printf ("Value of x in main is: %d\n", x);

	return 0;
}	// main

/*	================== fun ==================
	Increment and print global variable.
	   Pre  Global variable x has been defined
	   Post x incremented and printed
*/
void fun (void)
{
//	Statements
	x++;
	printf ("Value of x in fun is:  %d\n", x);
	return;
}	// fun

/*	Result:
Value of x in main is: 4
Value of x in fun is:  5
Value of x in main is: 5
*/