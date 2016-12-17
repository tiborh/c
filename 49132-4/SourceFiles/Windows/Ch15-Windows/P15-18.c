/*	===================== print ==================== 
	This function prints a singly linked queue.
	   Pre     pQueue is pointer to valid queue
	   Post    data in queue printed
*/
void print (QUEUE* pQueue)
{
//	Local Declarations 
	int printData;

//	Statements 
	printf("Queue contained:  ");
	while (dequeue(pQueue, &printData))
	    printf("%4d", printData);
	return;
}	// print 
