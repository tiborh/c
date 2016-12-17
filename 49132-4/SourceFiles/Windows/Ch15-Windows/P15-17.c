/*	================== insertData ==================
	This program creates random number data and 
	inserts them into a linked list queue.
	   Pre  pQueue is a pointer to first node 
	   Post Queue created and filled
*/
void insertData (QUEUE* pQueue)
{
//	Local Declarations 
	int  numIn;
	bool   success;

//	Statements 
	printf("Creating numbers: ");
	for (int nodeCount = 0; nodeCount < 5; nodeCount++)
	    {
	     // Generate random number 
	     numIn  = rand() % 999;
	     printf("%4d", numIn);
	     success = enqueue(pQueue, numIn);
	     if (!success)
	        {
	         printf("Error 101: Out of Memory\n");
	         exit (101);
	        } // if 
	    } // for 
	printf("\n");
	return;
}	// insertData 
