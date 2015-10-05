#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

int main(int argc, char **argv)
{
    int width, height;
    FILE *in;
    if (argc < 2)
    {
        printf("You need an input file.\n");
        return -1;
    }
    in = fopen(argv[1], "r");
    if (in == NULL)
    {
        printf("Could not open file: %s\n", argv[1]);
        return -1;
    }
    fscanf(in, "%d", &width);
    fscanf(in, "%d", &height);
    fgetc(in);
    char ** maze = (char **) malloc(height * sizeof(char*));
    int i;
    for(i = 0; i < height; i++)
    {
        maze[i] = (char *) malloc(width * sizeof(char));
    }
    char c;
    int x = 0, y = 0;

    while ((c = fgetc(in)) != EOF)
    {
        if (c == '\n')
        {
            y++;
            x = 0;
            continue;
        }
        else
        {
            //printf("%d %d\n", x, y);
            maze[y][x] = c;
            x++;
        }
    }

    int yStart, xStart;
    findStart(maze, width, height, &xStart, &yStart);
    if (xStart == -1 || yStart == -1)
    {
        printf("Could not find start of maze\n");
        return 0;
    }
    if (solveMazeDFS(maze, width, height, startX, startY))
    {
        if(checkMaze(maze, width, height))
            printf("Maze is correct!\n");
        else
            printf("Maze is incorrect!\n");
    }
    else
    {
        printf("Maze is unsolvable\n");
    }
    printMaze(maze, width, height);
    return 0;
}