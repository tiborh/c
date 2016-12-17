/*	================= dequeue ================
	This algorithm deletes a node from the queue.
	   Pre    queue is pointer to queue head structure 
	          dataOut is pointer to data being deleted
	   Post   Data pointer to queue front returned and
	          front element deleted and recycled.
	   Return true if successful; false if underflow 
*/
bool dequeue (QUEUE* queue, int* dataOut) 
{
//	Local Declarations 
	QUEUE_NODE* deleteLoc;

//	Statements 
	if (!queue->count)
	    return false;

	*dataOut = queue->front->data;
	deleteLoc = queue->front;
	if (queue->count == 1)
	   // Deleting only item in queue 
	   queue->rear  = queue->front = NULL;
	else
	   queue->front = queue->front->next;
	(queue->count)--;
	free (deleteLoc);

	return true;
}	// dequeue 
