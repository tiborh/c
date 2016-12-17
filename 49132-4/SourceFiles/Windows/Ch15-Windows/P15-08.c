/*	Test driver for list functions.
	   Written by: 
	   Date: 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//	Global Declarations
typedef int KEY_TYPE;
typedef struct
	{
	 KEY_TYPE key;
	} DATA;
typedef struct nodeTag
	{
	 DATA            data; 
	 struct nodeTag* link; 
	} NODE;

//	Function Declarations
NODE* insertNode (NODE*  pList, NODE*  pPre, DATA  item);
NODE* deleteNode (NODE*  List,  NODE*  pPre, NODE* pCur);
bool  searchList (NODE*  pList, NODE**   pPre, 
                  NODE** pCur,  KEY_TYPE target);
void  printList  (NODE*  pList);
NODE* buildList  (char*  fileID);
NODE* deleteKey  (NODE*  pList);
bool  getData    (FILE*  fpData, DATA* pData);

double averageList (NODE* pList);

//	Header file to include functions (Not in text)
#include "P15-LIST.H"

int main (void)
{
//	Local Declarations
	NODE*  pList;
	NODE*  pPre;
	NODE*  pCur;
	DATA   data;
	double avrg;
	char   more;

//	Statements
	printf("Begin list test driver\n\n");
	
	//	Build List
	pList = buildList("P15-LIST.DAT");
	if (!pList)
	   {
	    printf("Error building chron file\a\n");
	    exit  (100);
	   } // if
	printList (pList);
	
	printf("\nInsert data tests.\n");
	printf("Enter key:              ");
	scanf ("%d", &data.key);
	do
	   {
	    if (searchList (pList, &pPre, &pCur, data.key))
	        printf("Key already in list. Not inserted\n");
	    else
	        pList = insertNode(pList, pPre, data);
	    printf("Enter key <-1> to stop: ");
	    scanf ("%d", &data.key);
	   } while (data.key != -1);
	printList (pList);
	
	avrg = averageList(pList);
	printf("\nData average: %.1f\n", avrg);
	
	printf("\nDelete data tests.\n");
	do
	   {
	    pList = deleteKey (pList);
	    printf("Delete another <Y/N>: ");
	    scanf (" %c", &more);
	   } while (more == 'Y' || more == 'y');
	   
	printList (pList);
	printf("\nTests complete.\n");
	return 0;
} // main

/*	Results:
Begin list test driver

List contains: 
111 222 333 444 555 666 777 

Insert data tests.
Enter key:              50
Enter key <-1> to stop: -1
List contains:
 50 111 222 333 444 555 666 777 

Data average: 394.8

Delete data tests.
Enter key of node to be deleted: 50
Delete another <Y/N>: n
List contains:
111 222 333 444 555 666 777 

Tests complete.
*/