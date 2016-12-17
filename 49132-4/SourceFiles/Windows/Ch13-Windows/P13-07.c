/*	Shows application of some functions we have studied
	in this chapter. The program first creates a binary 
	file of integers. It then prints the file, first 
	sequentially and then randomly using rand().
	   Written by: 
	   Date: 
*/
#include <stdio.h>
#include <stdlib.h>

//	Function Declarations
void buildFile   (FILE** sp);
void printFile   (FILE*  sp);
void randomPrint (FILE*  sp);

//	Sub-Function Includes (not in text)
#include "P13-08.c"
#include "P13-09.c"
#include "P13-10.c"

int main (void) 
{
//	Local Declarations
	FILE* fpData; 

//	Statements
	buildFile   (&fpData);
	printFile   (fpData);
	randomPrint (fpData);
	return 0;
}	// main
