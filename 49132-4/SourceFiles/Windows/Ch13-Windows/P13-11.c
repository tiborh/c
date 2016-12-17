/*	This program merges two files
	   Written by: 
	   Date: 
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define READ_MODE  "rb"
#define WRITE_MODE "wb"

int main (void)
{
//	Local Declarations
	FILE*  spM1;
	FILE*  spM2;
	FILE*  spOut;

	int  recM1;
	int  recM2;
	int  sentinel    = INT_MAX;
	int  mergeCnt    = 0;

	char file1ID[]   = "P13Mrg1.bin";
	char file2ID[]   = "P13Mrg2.bin";
	char fileOutID[] = "P13Mrg3.bin";

//	Statements
	printf("Begin File Merge:\n");
	if (!(spM1 = fopen (file1ID, READ_MODE)))
	    printf("\aError on %s\n", file1ID), exit (100); 

	if (!(spM2 = fopen (file2ID, READ_MODE)))
	    printf("\aError on %s\n", file2ID), exit (200); 

	if (!(spOut = fopen (fileOutID, WRITE_MODE)))
	    printf("\aError on %s\n", fileOutID), exit (300); 

	fread (&recM1, sizeof(int), 1, spM1);
	if (feof(spM1)) 
	     recM1 = sentinel;
	fread (&recM2, sizeof(int), 1, spM2);
	if (feof(spM2)) 
	    recM2 = sentinel;

	while (!feof(spM1) || !feof(spM2))
	   {
	    if (recM1 <=  recM2)
	       {
	        fwrite (&recM1, sizeof(int), 1, spOut); 
	        mergeCnt++;
	        fread  (&recM1, sizeof(int), 1, spM1); 
	        if (feof(spM1)) 
	           recM1 = sentinel;
	       } // if
	    else
	       {
	        fwrite (&recM2, sizeof(int), 1, spOut);
	        mergeCnt++;
	        fread  (&recM2, sizeof(int), 1, spM2);
	        if (feof(spM2)) 
	           recM2 = sentinel;
	       } // else
	   } // while
	fclose (spM1);
	fclose (spM2);
	fclose (spOut);
	printf("End File Merge. %d items merged.\n", mergeCnt);
	return 0;
}	// main

/*	Results:
Begin File Merge:
End File Merge. 14 items merged.

Inut:   P13-Mrg1.bin:
		 14  17  18  21  23  25  31 

Input:  P13-Mrg2.bin:
		 10  12  15  16  19  27  28 

Output: P13-Mrg3.bin
		 10  12  14  15  16  17  18  19  21  23  25  27  28  31 
*/
