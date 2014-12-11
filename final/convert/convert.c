#include <stdio.h>
#include "vector.h"
#include "tree.h"

// FUNCTION DEFINITIONS
node * convert(node * root);


int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        return;
    }

    node * root = create_tree(argv[1]);

    convert(root);
}

node * convert(node * root)
{
    // TODO
}
