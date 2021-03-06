/*	==================== BST_Insert ====================
	This function uses recursion to insert the new data 
	into a leaf node in the BST tree.
	   Pre    Application has called BST_Insert, which  
	          passes root and data pointer
	   Post   Data have been inserted
	   Return pointer to [potentially] new root
*/
NODE* BST_Insert (BST_TREE* tree, 
                  NODE* root,     int dataIn)
{
//	Local Declarations
	NODE* newPtr;

//	Statements 

	if (!root)
	   {
	    // NULL tree -- create new node 
	    newPtr = malloc(sizeof (NODE));
	    if (!newPtr)
	       printf("Overflow in Insert\n"), exit (100);
	    newPtr->data = dataIn;
	    newPtr->left = newPtr->right = NULL;
	    return newPtr;
	   } // if

	// Locate null subtree for insertion 
	if (dataIn < root->data) 
	    root->left = BST_Insert(tree, root->left, 
	                            dataIn);
	else 
	   // new data >= root data 
	    root->right = BST_Insert(tree, root->right, 
	                             dataIn);
	return root;
}	// BST_Insert
