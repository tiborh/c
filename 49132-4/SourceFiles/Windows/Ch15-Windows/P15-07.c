/*	==================== deleteKey ====================
	Delete node from a linear list.
	   Pre   list is a pointer to the head of the list
	   Post  node has been deleted 
	         -or- a warning message printed if not found
	         returns pointer to first node (pList)
*/
NODE* deleteKey (NODE* pList)
{
//	Local Declarations
	int   key;
	NODE* pHead;
	NODE* pCur;
	NODE* pPre;

//	Statements
	printf("Enter key of node to be deleted: ");
	scanf ("%d", &key);
	
	if (!searchList(pList, &pPre, &pCur, key))
	    printf("%d is an invalid key\a\n", key);
	else
	    pHead = deleteNode (pList, pPre, pCur);
	     
	return pHead;
} // deleteKey
