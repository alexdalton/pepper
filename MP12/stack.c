#include <stdio.h>
#include "stack.h"

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
