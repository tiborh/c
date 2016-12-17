/*	Traverse a binary tree and print its data (integers)
	   Pre  root is entry node of a tree or subtree
	   Post each node has been printed
*/
void inOrder (NODE* root)
{
//	Statements
	if (root)
	   {
	    inOrder (root->left);
	    printf("%4d", root->data);
	    inOrder (root->right);
	   } // if
	return;
}	// preOrder
