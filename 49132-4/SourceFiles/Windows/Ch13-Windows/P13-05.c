/*	Reads text file of student data, and creates a binary file.
	   Written by: 
	   Date: 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//	Type Declarations
typedef struct stuData
	{
	 char  name[26];
	 char  id[5];
	 int   exams[3];
	 int   problems[8];
	 char  grade;
	} STU_DATA;

//	Function Declarations
bool getData         (FILE*     textFile, 
                      STU_DATA* aStudent);
void writeBinaryFile (STU_DATA* aStudent, 
                      FILE*     binFile); 

int main (void)
{
//	Local Declarations
	char* textFileID = "P13-stu.txt";
	char* binFileID  = "P13-stu.bin";

	STU_DATA aStudent;

	FILE* textFile;
	FILE* binFile;

//	Statements
	printf("\nBegin Student Binary File Creation\n ");
	if (!(textFile = fopen(textFileID, "r"))) 
	   {
	    printf("\nCannot open %s\n", textFileID);
	    exit (100);
	   } // if textFile
	if (!(binFile = fopen(binFileID, "wb")))
	   {
	    printf("\nCannot open %s\n", binFileID);
	    exit (200);
	   } // if binFile

	while (getData (textFile, &aStudent))
	   writeBinaryFile (&aStudent, binFile);

	fclose(textFile);
	fclose(binFile);
	printf("\n\nFile creation complete\n");
	return 0;
}	// main

/*	==================== getData ====================
	This function reads the text file.
	   Pre   textFile is opened for reading 
	   Post  data read and returned 
*/
bool getData (FILE* textFile, STU_DATA* aStu)
{
//	Local Declarations
	char  buffer[100];

//	Statements
	fgets(buffer, sizeof(buffer), textFile); 
	if (!feof(textFile))
	   {
	    sscanf(buffer, "%s %s %d%d%d%d%d%d%d%d%d%d%d %c",
	      aStu->name, aStu->id, 
	     &aStu->exams[0], &aStu->exams[1],&aStu->exams[2], 
	     &aStu->problems[0], &aStu->problems[1], 
	     &aStu->problems[2], &aStu->problems[3], 
	     &aStu->problems[4], &aStu->problems[5], 
	     &aStu->problems[6], &aStu->problems[7], 
	     &aStu->grade);
	    return true;
	   } // if
	return false;
} // getData

/*	================= writeBinaryFile =================
	Write student data to a binary file.
	   Pre   binFile is opened as a binary output file
	         aStudent is complete 
	   Post  Record written 
*/
void writeBinaryFile (STU_DATA* aStudent, FILE* binFile)
{
//	Local Declarations
	int amtWritten;

//	Statements
	amtWritten = fwrite (aStudent, 
	               sizeof(STU_DATA), 1, binFile);
	if (amtWritten != 1)
	   {
	    printf("Can�t write student file. Exiting\n");
	    exit (201);
	   } // if
	return;
} // writeBinaryFile

/*	Results:

Begin Student Binary File Creation
 

File creation complete

(To see output, you must run P13-06.c).
*/