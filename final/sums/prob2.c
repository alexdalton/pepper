#include <stdio.h>
#include "prob2.h"


void stackInit(stack * inStack)
{
    inStack->top = -1;
}

void pushStack(stack * inStack, int element)
{
    if (inStack->top >= (MAXSIZE - 1))
    {
        printf("Can't push onto stack: stack is full\n");
        return;
    }
    inStack->contents[++inStack->top] = element;
}

int popStack(stack * inStack)
{
    if(inStack->top < 0)
    {
        printf("Can't pop off stack: stack is empty\n");
        return -1;
    }
    return inStack->contents[inStack->top--];
}

void findPathRecursive(node * root, int expectedSum, int currentSum, stack * path)
{
    currentSum += root->value;
    stackPush(path, root->value);

    if( currentSum == expectedSum && root->left == NULL && root->right == NULL)
    {
        while(path->top >= 0)
        {
            printf("%d ", stackPop(path));
        }
        printf("\n");
    }
    if (root->left != NULL)
        findPathRecursive(root->left, expectedSum, currentSum, path);
    if (root->right != NULL)
        findPathRecursive(root->right, expectedSum ,currentSum, path);

    stackPop(path);
}

void findPath(node * root, int expectedSum)
{
    if (root == NULL)
        return;
    stack path;
    stackInit(&path);
    int currentSum = 0;
    findPathRecursive(root, expectedSum, currentSum, &path); 
}

int main()
{
    int sum;
    node root;
    node n1, n2, n3, n4, n5, n6;

    root.value = 1;
    n1.value = 1;
    n2.value = 2;
    n3.value = 3;
    n4.value = 4;
    n5.value = 5;
    n6.value = 6;

    root.left = &n1;
    root.right = &n2;
    n1.left = &n3;
    n1.right = &n4;
    n2.left = &n5;
    n2.right = &n6;
    n3.left = NULL;
    n3.right = NULL;
    n4.left = NULL;
    n4.right = NULL;
    n5.left = NULL;
    n5.right = NULL;
    n6.left = NULL;
    n6.right = NULL;

    printf("Please enter a sum: ");
    scanf("%d", &sum);

    findPath(&root, sum);
}
