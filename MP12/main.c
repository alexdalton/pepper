#include <stdio.h>
#include <stdlib.h>
#include "calculate.h"

#define POSTFIX 0
#define INFIX   1

int main(int argc, char *argv[])
{
	if (argc < 3) 
	{
		printf("Not enough arguments provided.\n");
		return -1;
	}

	int notation_type = atoi(argv[1]);
    if (notation_type == POSTFIX)
    	postfix(argv[2]);
    else if (notation_type == INFIX)
    	infix(argv[2]);
    else
    {
    	printf("Invalid notation type\n");
    	return -1;
    }

    return 0;
}