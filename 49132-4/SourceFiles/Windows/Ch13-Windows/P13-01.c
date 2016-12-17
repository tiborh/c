/*	Sample code to read binary file of integers.
	Code has been modified to add main funcion and to
	make elipses (...) comments.
	   Written by:
	   Date:
*/

#include <stdio.h>

int main (void)
{
		
//	As in text

{	//	Read a file of integers, three integers at a time.
//	…
//	Local Declarations
	FILE* spIntFile;
	int   itemsRead;
	int   intAry[3];

//	Statements
	spIntFile = fopen("int_file.dat", "rb");
//	 …
	while ((itemsRead = fread(intAry, 
	        sizeof(int), 3, spIntFile)) != 0)
	   {
	    // process array
//	         …
	   } // while
//	…

}	// block

//	End text

	return 0;
}	// main

