/*	==================== insertNode ====================
	This function inserts a single node into a linear list.
	   Pre   pList is pointer to the list; may be null
	         pPre points to new node’s predecessor
	         item contains data to be inserted
	   Post  returns the head pointer
*/
NODE* insertNode (NODE* pList, NODE* pPre, DATA item)
{
//	Local Declarations
	NODE* pNew;

//	Statements
	if (!(pNew  = (NODE*)malloc(sizeof(NODE)))) 
	    printf("\aMemory overflow in insert\n"),
	           exit (100); 

	pNew->data = item;
	if (pPre == NULL) 
	   {
	    // Inserting before first node or to empty list
	    pNew->link  = pList;
	    pList       = pNew;
	   } // if pPre
	else
	   {
	    // Inserting in middle or at end
	    pNew->link = pPre->link;
	    pPre->link = pNew;
	   } // else
	return pList;
}	// insertNode
