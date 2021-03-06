/*	================== insertData ==================
	This program creates random numbers and 
	inserts them into a linked list stack.
	   Pre  pStack is a pointer to first node 
	   Post Stack has been created 
*/
void insertData (STACK* pStack)
{
//	Local Declarations 
	int  numIn;
	bool success;

//	Statements 
	printf("Creating numbers: ");
	for (int nodeCount = 0; nodeCount < 10; nodeCount++)
	    {
	     // Generate random number 
	     numIn  = rand() % 999;
	     printf("%4d", numIn);
	     success = push(pStack, numIn);
	     if (!success)
	        {
	         printf("Error 101: Out of Memory\n");
	         exit (101);
	        } // if 
	    } // for 
	printf("\n");
	return;
}	// insertData 
