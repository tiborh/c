/*	Demonstrate the binary search tree insert and 
	traversals.
	   Written by:
	   Date:
*/
#include <stdio.h>
#include <stdlib.h>

//	Global Declarations
typedef struct node
  {
   int          data;
   struct node* left;
   struct node* right;
  } NODE;

typedef struct
  {
   int   count;
   NODE* root;
  } BST_TREE;

//	Function Declarations
void  preOrder   (NODE* root);
void  inOrder    (NODE* root);
NODE* BST_Insert (BST_TREE* tree, 
                  NODE* root,     int data);

//	Include subfunctions (Not in text)
#include "P15-TREE.H"

int main (void)
{
//	Local Declarations
	int      numIn;
	BST_TREE tree;

//	Statements
	printf("Please enter a series of integers."
	       "\nEnter a negative number to stop\n");

	tree.count = 0;
	tree.root  = NULL;
	do 
	   {
	    printf("Enter a number: ");
	    scanf("%d", &numIn);
	    if (numIn > 0)
	       {
	        tree.root = BST_Insert 
	            (&tree, tree.root, numIn);
	        tree.count++;
	       } // if
	   } while (numIn > 0);

	printf("\nData in preOrder: ");
	preOrder (tree.root);

	printf("\n\nData in inOrder:  ");
	inOrder (tree.root);

	printf("\n\nEnd of BST Demonstration\n");
	return 0;
}	// main

/*	Results
Please enter a series of integers.
Enter a negative number to stop
Enter a number: 45
Enter a number: 54
Enter a number: 23
Enter a number: 32
Enter a number: 3
Enter a number: -1

Data in preOrder:   45  23   3  32  54

Data in inOrder:     3  23  32  45  54

End of BST Demonstration
*/