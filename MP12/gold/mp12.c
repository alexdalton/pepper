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

int get_precedence(char c)
{
    switch (c)
    {
        case '*': return 10;
        case '/': return 10;
        case '+': return 9;
        case '-': return 9;
        default: return 0;
    }
}

int is_op(char c)
{
    return (c == '*') || (c == '/') || (c == '+') || (c == '-');
}

void infix(char * exp_str)
{
	unsigned int i;
    int top = -1;
    char stack[100];
    char output[100];
    int outputSize = 0;
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
                while (top >= 0 && is_op(stack[top]) && get_precedence(c) <= get_precedence(stack[top]))
                {
                    output[outputSize++] = stack[top--];
                    //printf("122 Popping: %c\n", output[outputSize - 1]);
                }
                //printf("124 Pushing: %c\n", c);
                stack[++top] = c; 
                break;				
            }
            case '(': 
            {
                stack[++top] = c;
                //printf("128 Pushing: %c\n", c);
                break;
            }
            case ')':
            {
                while (top >= 0 && stack[top] != '(')
                {
                    output[outputSize++] = stack[top--];
                    //printf("132 Popping: %c\n", output[outputSize - 1]);
                }
                if (top >= 0 && stack[top] == '(')
                    //printf("136 Popping: (\n");
                    top--;
                break;
            }
			default:
            {
                output[outputSize++] = c;
                output[outputSize] = '\0';
                //printf("142 Output: %s\n", output);
				break;
            }
	    }
    }
    while (top >= 0)
    {
        output[outputSize++] = stack[top--];
        //printf("150 Popping: %c\n", output[outputSize - 1]);
    }
    output[outputSize] = '\0';
    //printf("%s\n", output);
    postfix(output); 
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
