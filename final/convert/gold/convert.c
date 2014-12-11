#include <stdio.h>
#include "tree.h"

// FUNCTION DEFINITIONS
node * convert(node * root);
void convertRecursive(node * current, node ** lastNode);
void printList(node * head);

int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        return -1;
    }

    node * root = create_tree(argv[1]);
    root = convert(root);
    printList(root);
    deleteList(root);
}

node * convert(node * root)
{
    node * lastNode = NULL;
    convertRecursive(root, &lastNode);

    node * head = lastNode;
    while (head != NULL && head->left != NULL)
        head = head->left;
    return head;
}

void convertRecursive(node * current, node ** lastNode)
{
    if (current == NULL)
        return;

    if (current->left != NULL)
        convertRecursive(current->left, lastNode);

    current->left = *lastNode;

    if (*lastNode != NULL)
        (*lastNode)->right = current;

    *lastNode = current;

    if (current->right != NULL)
        convertRecursive(current->right, lastNode);
}



void printList(node * head)
{
    node * previous;
    printf("Left to right traversal: \n");
    while (head != NULL)
    {
        printf("%d ", head->value);
        previous = head;
        head = head->right;
    }
    printf("\nRight to left traversal: \n");
    head = previous;
    while (head != NULL)
    {
        printf("%d ", head->value);
        head = head->left;
    }
    printf("\n");
}
