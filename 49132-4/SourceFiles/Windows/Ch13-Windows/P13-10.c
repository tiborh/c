/*	=================== randomPrint =================== 
	This function randomly prints the file. Some data may
	be printed twice, depending on the random numbers
	generated.
	   Pre  spData is an open file 
	   Post Ten records have been printed
*/
void randomPrint (FILE* spData) 
{
//	Local Declarations
	int data;
	int randomSeek;

//	Statements
	printf("\nFile contents in random sequence.\n");
	for (int i = 0; i < 10; i++)
	   {
	    randomSeek =  (rand() % 10);
	    fseek(spData, 
	          sizeof(int) * randomSeek, SEEK_SET); 
	    fread(&data, sizeof(int), 1, spData);
	    printf("Record %3d ==> %3d\n", randomSeek, data);
	   } // for
	return;
}	// randomPrint

/*	Results:
File contents in random sequence.
Record   8 ==>  81
Record   8 ==>  81
Record   3 ==>  16
Record   5 ==>  36
Record   1 ==>   4
Record   7 ==>  64
Record   0 ==>   1
Record   9 ==> 100
Record   2 ==>   9
Record   6 ==>  49
*/