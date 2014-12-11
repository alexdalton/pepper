#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "queue.h"

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

// Recursive helper function for inserting nodes into the tree
void insert(node * root, int value)
{
    if (value < root->value)
    {
        if(root->left != NULL)
        {
            insert(root->left, value);
        }
        else
        {
            root->left = (node *) malloc(sizeof(node));
            root->left->value = value;
            root->left->left = NULL;
            root->left->right = NULL;
        }
    }
    else if (value >= root->value)
    {
        if (root->right != NULL)
        {
            insert(root->right, value);
        }
        else
        {
            root->right = (node *) malloc(sizeof(node));
            root->right->value = value;
            root->right->left = NULL;
            root->right->right = NULL;
        }
    }
}

/* create_tree - given a file creates a tree from the file contents
*  INPUT: fileName - name of file containing the tree information
*  OUTPUT: allocates memory and creates a tree
*  RETURN: returns a pointer to the root of the tree
*/
node * create_tree(char * fileName)
{
	int value;
    FILE * fp;
    if ((fp = fopen(fileName, "r")) == NULL)
    {
        printf("Error opening file: %s\n", fileName);
        return NULL;
    }

    if (fscanf(fp, "%d", &value) != 1)
    {
        printf("%s is incorrectly formatted\n", fileName);
        return NULL;
    }
    
    node * root = (node *) malloc(sizeof(node));
    root->value = value;
    root->left = NULL;
    root->right = NULL;
    queue q;
    initQueue(&q);

    //printf("Enqueueing %d\n", root->value);
    enqueue(&q, root); 

    while (!isEmpty(&q))
    {
        node * current = dequeue(&q);
        if (fscanf(fp, "%d", &value) != 1)
            break;
        node * left = (node *) malloc(sizeof(node));
        left->value = value;
        left->left = NULL;
        left->right = NULL;
        current->left = left;
     //   printf("Setting %d left to %d\n", current->value, left->value);
        enqueue(&q, left);

         if (fscanf(fp, "%d", &value) != 1)
            break;
        node * right = (node *) malloc(sizeof(node));
        right->value = value;
        right->left = NULL;
        right->right = NULL;
        current->right = right;
    //    printf("Setting %d right to %d\n", current->value, right->value);
        enqueue(&q, right);
    }

	return root;
}

