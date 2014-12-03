#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mp12.h"

/* Given the root of a tree, frees the tree structure from memory */
void delete_tree(node * curNode)
{
	if (curNode == NULL)
		return;
	delete_tree(curNode->left);
	delete_tree(curNode->right);
	free(curNode);
}

node * create_postfix_tree(char * exp_str)
{
	unsigned int i;
	stack s1;
	stackInit(&s1);
	for (i = 0; i < strlen(exp_str); i++)
	{
		char c = exp_str[i];
		switch(c)
		{
            case ' ': break;
			case '+':
			case '-':
			case '*':
			case '/':
            {
				node * new_node = (node*) malloc(sizeof(node));
				new_node->item = c;
				new_node->right = stackPop(&s1);
				new_node->left = stackPop(&s1);
                //printf("Pushing: %c with left %c and right %c\n", new_node->item,
                //       new_node->left->item, new_node->right->item);
				stackPush(&s1, new_node);
				break;
            }
			default:
            {
				node * new_node = (node*) malloc(sizeof(node));
				new_node->item = c;
				new_node->left = NULL;
				new_node->right = NULL;
                //printf("Pushing: %c\n", new_node->item);
				stackPush(&s1, new_node);
				break;
            }
	    }
    }
	return stackPop(&s1);
}

int evaluate_postfix(node * curNode)
{
	if (curNode->left == NULL && curNode->right == NULL)
		return (int) curNode->item - '0';
	
    char operation = curNode->item;
    switch(operation)
    {
        case '+':
            return evaluate_postfix(curNode->left) + evaluate_postfix(curNode->right); 
        case '-':
            return evaluate_postfix(curNode->left) - evaluate_postfix(curNode->right); 
        case '*':
            return evaluate_postfix(curNode->left) * evaluate_postfix(curNode->right); 
        case '/':
            return evaluate_postfix(curNode->left) / evaluate_postfix(curNode->right);
        default:
            return 0; 
    }
}

void postfix(char * exp_str)
{
	node * root = create_postfix_tree(exp_str);
	printf("%d\n", evaluate_postfix(root));
	delete_tree(root);
}

void infix(char * exp_str)
{
    // CHALLENGE CODE GOES HERE
}

void stackInit(stack * myStack)
{
	myStack->top = -1;
}

void stackPush(stack * myStack, node * element)
{
	if (myStack->top >= (MAXSIZE - 1))
	{
		printf("Can't push onto stack: stack is full\n");
		return;
	}
	myStack->contents[++myStack->top] = element;
}

node * stackPop(stack * myStack)
{
	if(myStack->top < 0)
	{
		printf("Can't pop off stack: stack is empty\n");
		return NULL;
	}
	return myStack->contents[myStack->top--];
}
