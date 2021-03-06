/*	==================== searchList ====================
	Given key value, finds the location of a node
	   Pre   pList points to a head node
	         pPre points to variable to receive pred
	         pCur points to variable for current node
	         target is key being sought
	   Post  pCur points to first node with >= key
	         -or- null if target > key of last node
	         pPre points to largest node < than key
	         -or- null if target < key of first node
	         function returns true if found
	                          false if not found 
*/
bool searchList (NODE*  pList, NODE**   pPre,
                 NODE** pCur,  KEY_TYPE target)
{
//	Local Declarations
	bool found = false; 

//	Statements
	*pPre = NULL;
	*pCur = pList;

	// start the search from beginning
	while (*pCur != NULL && target > (*pCur)->data.key)
	   {
	    *pPre = *pCur; 
	    *pCur = (*pCur)->link; 
	   } // while

	if (*pCur && target == (*pCur)->data.key) 
	   found = true;
	return found;
}	// searchList
