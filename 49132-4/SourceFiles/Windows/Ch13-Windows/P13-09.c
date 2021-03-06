/*	=================== printFile ===================
	Prints the file starting at the first record.
	   Pre   spData is an open file 
	   Post  file has been printed 
*/
void printFile (FILE* spData) 
{
//	Local Declarations
	int data;
	int recNum;
	
//	Statements
	recNum = 0;
	rewind(spData);
	fread(&data , sizeof(int), 1, spData);
	while (!feof(spData))
	   {
	    printf("Record %2d: %3d\n", recNum++, data);
	    fread(&data, sizeof(int), 1, spData);
	   } // while
	return;
}	// printFile

/*	Results:
Record 0:   1
Record 1:   4
Record 2:   9
Record 3:  16
Record 4:  25
Record 5:  36
Record 6:  49
Record 7:  64
Record 8:  81
Record 9: 100
*/