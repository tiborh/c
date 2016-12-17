/*	Writes one studentís record to a binary file. 
	   Pre  aStudent has been filled 
	        spOut is open for writing 
	   Post aStudent written to spOut 
*/
void writeStudent (STU* aStudent, FILE* spOut)
                   
{
//	Local Declarations
	int ioResult;

//	Statements
	ioResult = fwrite(aStudent, 
	                  sizeof(STU), 1, spOut);
	if (ioResult != 1) 
	   {
	    printf("\a Error writing student file \a\n");
	    exit (100);
	   } // if
	return;
}	// writeStudent
