/*	This function averages the values in a linear list.
	   Pre   pList is a pointer to a linear list 
	   Post  list average is returned 
*/
double averageList (NODE* pList)
{
//	Local Declarations
	NODE* pWalker;
	int   total;
	int   count;

//	Statements
	total   = count = 0;
	pWalker = pList;
	while (pWalker)
	   {
	    total += pWalker->data.key;
	    count++;
	    pWalker = pWalker->link;
	   } // while
	return (double)total / count;
} // averageList
