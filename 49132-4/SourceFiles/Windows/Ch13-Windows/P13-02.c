/*	This program is a driver to test program 1 (read
	student file) and 2 (write student file).
	   Written by: 
	   Date: 
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Global Structures 
typedef struct stuData
	{
	 char     name[26];
	 int      id;
	 int      exams[3];
	 int      problems[8];
	 char     grade;
	} STU;

//  Prototype Declarations 
	void writeStudent (STU *aStudent,   FILE *fileOut);
	int  readStudent  (STU *oneStudent, FILE *stuFile);

//	Include Program 3
#include "P13-03.c"

int main (void)
{
// Local Variables 
	char stuFileID[] = "students.bin";
	char outFileID[] = "students.out";

	STU stuData[5] = 
		{ {"Able Aah",  1111, {90, 91, 92}, {9, 9, 9, 9, 9, 9, 9, 10}, 'A'},
		  {"Betty Bee", 2222, {80, 81, 82}, {8, 8, 8, 8, 8, 8, 8, 9},  'B'},
		  {"Charl Cee", 3333, {70, 71, 72}, {7, 7, 7, 7, 7, 7, 7, 8},  'C'},
		  {"Dick Dee",  4444, {60, 61, 62}, {6, 6, 6, 6, 6, 6, 6, 7},  'D'},
		  {"Frank Eff", 5555, {50, 51, 52}, {5, 5, 5, 5, 5, 5, 5, 6},  'F'} };

	STU aStudent;

	FILE *stuFile;
	FILE *outFile;

// Statements 
	printf("Begin Test. Creating File.\n\n");

	if (!(outFile = fopen(outFileID, "wb"))) 
		{
		 printf("\nCannot open %s for creation\n", outFileID);
		 exit (200);
		} // if 
	
	for (int i = 0; i < 5; i++)
	   {
	    aStudent = stuData[i];
	    writeStudent (&aStudent, outFile);               
	   } // for
	fclose(outFile);

	// Now read file 
	if (!(stuFile = fopen(outFileID, "rb"))) 
		{
		 printf("\nCannot open %s for reading\n", outFileID);
		 exit (200);
		} // if 
	
	readStudent (&aStudent, stuFile);
	while (!feof(stuFile))
		{
	     printf("%-25s",     aStudent.name);
	     printf("%6d",       aStudent.id);
	     printf(" %2c ",     aStudent.grade);
		 printf("%3d",       aStudent.exams[0]);
		 printf("%3d %3d\n", aStudent.problems[0], aStudent.problems[7]);
		 readStudent       (&aStudent, stuFile);
		} // while 

	fclose(stuFile);
	printf("\nEnd of Test\n"); 

	return 0;
}	// main 

/*	Reads one studentís data from a file 
	   Pre   spStuFile is opened for reading
	   Post  stu data structure filled
	         ioResults returned
*/
int readStudent (STU* oneStudent, FILE* spStuFile)
{
//	Local Declarations
	int ioResults;
	
//	Statements
	ioResults = fread(oneStudent, 
	                  sizeof(STU), 1, spStuFile);
	return ioResults;
} // readStudent

/*	Results:

Begin Test. Creating File.

Able Aah                   1111  A  90  9  10
Betty Bee                  2222  B  80  8   9
Charl Cee                  3333  C  70  7   8
Dick Dee                   4444  D  60  6   7
Frank Eff                  5555  F  50  5   6

End of Test
*/