/*	Traverse a binary tree and print its data (integers)
	   Pre  root is entry node of a tree or subtree
	   Post each node has been printed
*/
void preOrder (NODE* root)
{
//	Statements
	if (root)
	   {
	    printf("%4d", root->data);
	    preOrder (root->left);
	    preOrder (root->right);
	   } // if
	return;
}	// preOrder
