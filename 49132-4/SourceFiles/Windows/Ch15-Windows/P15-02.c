/*	==================== deleteNode ====================
	This function deletes a single node from the link list.
	   Pre   pList is a pointer to the head of the list
	         pPre points to node before the delete node
	         pCur points to the node to be deleted
	   Post  deletes and recycles pCur
	         returns the head pointer
*/
NODE* deleteNode (NODE* pList, NODE* pPre, NODE* pCur)
{
//	Statements
	if (pPre == NULL) 
	   // Deleting first node
	   pList = pCur->link;
	else
	   // Deleting other nodes
	   pPre->link = pCur->link;
	free  (pCur);
	return pList;
}	// deleteNode
