#include <stdio.h>
#include "vector.h"
#include "tree.h"

// FUNCTION DEFINITIONS
void findPathRecursive(node * root, int expectedSum, int currentSum, vector * path);
void findPath(node * root, int expectedSum);


int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        return -1;
    }

    node * root = create_tree(argv[1]);
    int sum;
    printf("Please enter a sum: ");
    scanf("%d", &sum);

    findPath(root, sum);
    delete_tree(root);
}

void findPathRecursive(node * root, int expectedSum, int currentSum, vector * path)
{
    currentSum += root->value;
    pushBack(path, root->value);

    if( currentSum == expectedSum && root->left == NULL && root->right == NULL)
    {
        int i;
        for (i = 0; i <= path->back; i++)
        {
            printf("%d ", path->contents[i]);
        }
        printf("\n");
    }
    if (root->left != NULL)
        findPathRecursive(root->left, expectedSum, currentSum, path);
    if (root->right != NULL)
        findPathRecursive(root->right, expectedSum ,currentSum, path);

    if (!isEmpty(path))
        popBack(path);
}

void findPath(node * root, int expectedSum)
{
    if (root == NULL)
        return;
    vector path;
    vectorInit(&path);
    int currentSum = 0;
    findPathRecursive(root, expectedSum, currentSum, &path); 
}
