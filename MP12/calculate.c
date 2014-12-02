#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

/* Given the root of a tree, frees the tree structure from memory */
void delete_tree(node * curNode)
{
	if (curNode == NULL)
		return;
	delete_tree(curNode->left);
	delete_tree(curNode->right);
	free(curNode);
}

node * create_tree(char * exp_str)
{
	int i;
	stack s1;
	stackInit(&s1);
	for (i = 0; i < strlen(exp_str); i++)
	{
		char c = expression[i];
		switch(c)
		{
			case '+':
			case '-':
			case '*':
			case '/':
				{
					node * new_node = (node*) malloc(sizeof(node));
					new_node->item = c;
					new_node->right = stackPop(&s1);
					new_node->left = stackPop(&s1);
					stackPush(&s1, new_node);
					break;
				}
			default:
				{
					node * new_node = (node*) malloc(sizeof(node));
					new_node->item = c;
					new_node->left = NULL;
					new_node->right = NULL;
					stackPush(&s1, new_node);
					break;
				}
		}
	}
	return stackPop(&s1);
}

void evaluate(node * curNode)
{
	if (curNode == NULL)
		return;
	evaluate(curNode->left);
	evaluate(curNode->right);
	print("%c ", curNode->item);
}

void postfix(char * exp_str)
{
	node * root = create_tree(exp_str);
	evaluate(root);
	delete_tree(root);
}

void infix(char * exp_str;)
{
    // CHALLENGE CODE GOES HERE
}