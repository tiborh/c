/*	Makes binary file of integers.
	   Written by:
	   Date:
*/
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
//	Local Definitions 
	int   i;
	int   limit;
	int   ioResult;
	char  fileID[20];
	FILE *fp;
	
//	Statements 
	printf("Make binary file. How many integers: ");
	scanf ("%d", &limit);
	
	printf("File name: ");
	scanf ("%19s", fileID);
	
	printf("Starting number: ");
	scanf ("%d", &i);
	limit = limit + i * 2;
	
	if (!(fp = fopen (fileID, "wb")))
	    printf("\aCan’t open %s\n", fileID), exit (100);
	
	printf("Writing: ");
	for ( ; i < limit; i += 2)
	    {
	     ioResult = fwrite (&i, sizeof(int), 1, fp);
	     if (ioResult == 1)
	         printf("%4d ", i);
	     else
	         printf("\nError writing data: %d\n", ioResult),
	         exit (100);
	    } // for
	fclose (fp);    
	printf("\nEnd of file creation");
	
	return 0;
}	// main 

/*	Create First File
Make binary file. How many integers: 5
File name:  P13-04F1.dat
Starting number: 13
Writing:   13   15   17   19   21   23   25   27   29
End of file creation

	Create Second File
Make binary file. How many integers: 8
File name:  P13-04F2.dat
Starting number: 10
Writing:   10   12   14   16   18   20   22   24   26
End of file creation
*/