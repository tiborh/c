/*	This program is a test driver to demonstrate the 
	basic operation of the stack push and pop functions. 
	   Written by: 
	   Date:       
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//	Global Declarations 
typedef struct node
   {
    int         data;
    struct node* link;
   } STACK_NODE;

typedef struct
   {
    int         count;
    STACK_NODE* top;
   } STACK;

//	Function Declarations 
void insertData (STACK* pStack);
void print      (STACK* pStack);
bool push       (STACK* pList, int  dataIn);
bool pop        (STACK* pList, int* dataOut);

//	Header file for stack functions (Not in text)
#include "P15-STACK.H"

int main (void)
{
//	Local Declarations 
STACK* pStack;

//	Statements 
	printf("Beginning Simple Stack Program\n");

	pStack = malloc(sizeof(STACK));
	if (!pStack)
	   printf("Error allocating stack"), exit(100);

	pStack->top   = NULL;
	pStack->count = 0;
	insertData (pStack);
	print      (pStack);

	printf("\nEnd Simple Stack Program\n");
	return 0;
}	// main 

/*	Results:
Beginning Simple Stack Program
Creating numbers:  854 763 123 532  82 632  33 426 228  90
Stack contained:    90 228 426  33 632  82 532 123 763 854
End Simple Stack Program
*/