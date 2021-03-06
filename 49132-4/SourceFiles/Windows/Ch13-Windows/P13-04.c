/*	This program appends two binary files of integers.
	   Written by: 
	   Date: 
*/
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
//	Local Declarations
FILE* sp1;
FILE* sp2;
int   data;
long  dataCount;
char  fileID[13];

//	Statements
	printf("This program appends two files.\n");
	printf("Please enter the file ID of the primary file: "); 
	scanf("%12s", fileID);
	if (!(sp1 = fopen (fileID, "ab")))
	    printf("\aCan�t open %s\n", fileID), exit (100);

	if (!(dataCount = (ftell (sp1))))
	   printf("\a%s has no data\n", fileID), exit (101); 
	dataCount /= sizeof(int);

	printf("Please enter the file ID of the second file: ");  
	scanf("%12s", fileID);
	if (!(sp2 = fopen (fileID, "rb")))
	   printf("\aCan�t open %s\n", fileID), exit (110);

	while (fread (&data, sizeof(int), 1, sp2) == 1)
	   {
	    fwrite (&data, sizeof(int), 1, sp1);
	    dataCount++;
	   } // while

	if (! feof(sp2))
	   printf("\aRead Error. No output.\n"), exit (120); 

	fclose (sp1);
	fclose (sp2);

	printf("Append complete: %ld records in file\n",  
	        dataCount);
	return 0;
}	// main

/*	Results:
This program appends two files.
Please enter the file ID of the primary file: P13-04F1.dat
Please enter the file ID of the second file: P13-04F2.dat
Append complete: 18 records in file
*/