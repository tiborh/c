/*	===================== print ==================== 
	This function prints a singly linked stack.
	   Pre     pStack is pointer to valid stack
	   Post    data in stack printed
*/
void print (STACK* pStack)
{
//	Local Declarations 
	int printData;

//	Statements 
	printf("Stack contained:  ");
	while (pop(pStack, &printData))
	    printf("%4d", printData);
	return;
}	// print 
