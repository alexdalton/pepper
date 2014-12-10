#include <stdlib.h>
#include "tree.h"

/*  delete_tree - given the root of a tree deletes it, freeing memory
*   INPUT: root - the root of the tree
*	OUTPUT: deletes the tree
*	RETURN: none
*/
void delete_tree(node * root)
{
	if (root == NULL)
		return;
	delete_tree(root->left);
	delete_tree(root->right);
	free(root);
}

/* create_tree - given a file creates a tree from the file contents
*  INPUT: fileName - name of file containing the tree information
*  OUTPUT: allocates memory and creates a tree
*  RETURN: returns a pointer to the root of the tree
*/
node * create_tree(char * fileName)
{
	FILE * fp = open(fileName, "r");
	char c;
	// TODO
	close(fp);
}