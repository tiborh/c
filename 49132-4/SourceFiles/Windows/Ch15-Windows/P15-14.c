/*	================= enqueue ================
	This algorithm inserts data into a queue.
	   Pre    queue is valid 
	   Post   data have been inserted 
	   Return true if successful, false if overflow 
*/
bool enqueue (QUEUE* queue, int dataIn) 
{
//	Local Declarations 
	QUEUE_NODE* newPtr;

//	Statements 
	if (!(newPtr = malloc(sizeof(QUEUE_NODE))))
	   return false;

	newPtr->data = dataIn; 
	newPtr->next = NULL; 

	if (queue->count == 0)
	   // Inserting into null queue 
	   queue->front  = newPtr;
	else
	   queue->rear->next = newPtr; 
	(queue->count)++;
	queue->rear = newPtr;
	return true;
}	// enqueue 
