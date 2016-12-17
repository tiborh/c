/*	Traverse and print a linear list. 
	   Pre   pList is a valid linear list
	   Post  List has been printed
*/
void printList (NODE* pList) 
{
//	Local Declarations
	NODE* pWalker;

//	Statements
	pWalker = pList;
	printf("List contains:\n");

	while (pWalker)
	   {
	    printf("%3d ", pWalker->data.key);
	    pWalker = pWalker->link;
	   } // while
	printf("\n");
	return;
} // printList
