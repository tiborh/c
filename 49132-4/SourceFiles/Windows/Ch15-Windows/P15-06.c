/*	==================== buildList ====================
	This program builds a key-sequenced linear list.
	   Pre   fileID is file that contains data for list 
	   Post  list built
	         returns pointer to head of list
*/
NODE* buildList (char* fileID)
{
//	Local Declarations
	DATA  data;
	NODE* pList;
	NODE* pPre;
	NODE* pCur;
	FILE* fpData;

//	Statements
	pList = NULL;
	
	fpData = fopen(fileID, "r");
	if (!fpData)
	   {
	    printf("Error opening file %s\a\n", fileID);
	    exit (210);
	   } // if open fail
	
	while (getData (fpData, &data))
	   {
	    // Determine insert position
	    searchList (pList, &pPre, &pCur, data.key);
	    pList = insertNode(pList, pPre, data);
	   } // while
	return pList;
} // buildList
