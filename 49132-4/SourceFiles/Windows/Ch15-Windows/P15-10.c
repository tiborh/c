/*	=================== pop ====================
	Delete node from linked list stack. 
	   Pre     pStackTop is pointer to valid stack
	   Post    dataOut contains deleted data
	   Return  true  if successful
	           false if underflow
*/
bool pop (STACK* pStack, int* dataOut)
{
//	Local Declarations 
	STACK_NODE* pDlt;
	bool        success;

//	Statements 
	if (pStack->top)             // Test for Empty Stack
	   {
	    success  = true;
	    *dataOut = pStack->top->data;
	    pDlt     = pStack->top;
	    pStack->top = (pStack->top)->link;
	    pStack->count--;
	    free (pDlt);
	   } // else 
	else
	   success = false;
	return success;
}	// pop 
