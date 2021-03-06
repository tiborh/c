/*	This program is a test driver to demonstrate the 
	basic operation of the enqueue and dequeue functions. 
	   Written by: 
	   Date:       
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//	Global Declarations 
typedef struct node
   {
    int          data;
    struct node* next;
   } QUEUE_NODE;

typedef struct
   {
    QUEUE_NODE* front;
    int         count;
    QUEUE_NODE* rear;
   } QUEUE;

//	Function Declarations 
void insertData (QUEUE* pQueue);
void print      (QUEUE* pQueue);
bool enqueue    (QUEUE* pList, int  dataIn);
bool dequeue    (QUEUE* pList, int* dataOut);

//	Queue header file (not in text)
#include "P15-QUEUE.H"

int main (void)
{
//	Local Declarations 
QUEUE* pQueue;

//	Statements 
	printf("Beginning Simple Queue Program\n");

	pQueue = malloc(sizeof(QUEUE));
	if (!pQueue)
	   printf("Error allocating queue"), exit(100);

	pQueue->front = NULL;
	pQueue->count = 0;
	pQueue->rear  = NULL;

	insertData (pQueue);
	print      (pQueue);

	printf("\nEnd Simple Queue Program\n");
	return 0;
}	// main 

/*	Results:
Beginning Simple Queue Program
Beginning Simple Queue Program
Creating numbers:  854 763 123 532  82
Queue contained:   854 763 123 532  82
End Simple Queue Program
*/