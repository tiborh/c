/*	Prints binary file of integers.
	   Written by:
	   Date:
*/
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
//	Local Definitions 
	int   intIn = 0;
	int   ioResult;
	char  fileID[20];
	FILE *fp;
	
//	Statements 
	printf("Prints binary file.\n");
	printf("File name: ");
	scanf ("%19s", fileID);
	
	if (!(fp = fopen (fileID, "rb")))
	    printf("\aCan�t open %s\n", fileID), exit (100);
	
	do
	   {
	    ioResult = fread(&intIn, sizeof(int), 1, fp);
	    if (ioResult == 1)
	        printf("%3d ", intIn);
	   } while (!feof(fp));
	printf("\n");
	
	fclose (fp);    
	printf("End of file print");
	
	return 0;
}	// main 

/*	Create First File
Make binary file. How many integers: 5
File name:  P13-04-F1.dat
Starting number: 13
End of file creation

	Create Second File
Make binary file. How many integers: 8
File name:  P13-04-F2.dat
Starting number: 10
End of file creation
*/