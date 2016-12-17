/*	=================== buildFile ===================
	Creates a disk file that we can process randomly.
	   Pre   nothing 
	   Post  file has been built 
*/
void buildFile (FILE** spData) 
{
//	Local Declarations
	int  data;
	
//	Statements
	if (!(*spData = fopen("SAMPLE.DAT", "w+b"))) 
	   {
	    printf("\aError opening file.\n"); 
	    exit (100);
	   } // if open
	for (int i = 1; i <= 10; i++) 
	    {
	     data = i * i;
	     fwrite(&data, sizeof(int), 1, *spData);
	    } // for
	return;
}	// buildFile
