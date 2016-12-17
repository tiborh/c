/*	=================== push ====================
	Inserts node into linked list stack. 
	   Pre    pStack is pointer to valid stack header
	   Post   dataIn inserted 
	   Return true  if successful
	          false if underflow
*/
bool push (STACK* pStack, int dataIn)
{
//	Local Declarations 
	STACK_NODE* pNew;
	bool        success;

//	Statements 
	pNew = (STACK_NODE*)malloc(sizeof (STACK_NODE));
	if (!pNew)
	    success = false;
	else
	   {
	    pNew->data  = dataIn;
	    pNew->link  = pStack->top;
	    pStack->top = pNew;
	    pStack->count++;
	    success = true;
	   } // else 
	return success;
}	// push 
