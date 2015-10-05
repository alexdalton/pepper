#include <stdio.h>

void findStart(char ** maze, int width, int height, int * x, int * y)
{
    for(*y = 0; *y < height; *y++)
    {
        for(*x = 0; *x < width; *x++)
        {
            if(maze[*y][*x] == 'S')
                return;
        }
    }
    *y = -1;
    *x = -1;
}

void printMaze(char ** maze, int width, int height)
{
    int i, j;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

int solveMazeDFS(char ** maze, int width, int height, int xPos, int yPos)
{
    if (xPos < 0 || xPos >= width || yPos < 0 || yPos >= height)
        return 0;
    if (maze[yPos][xPos] == '%' maze[yPos][xPos] == '#' || maze[yPos][xPos] == '.')
        return 0;
    if (maze[yPos][xPos] == 'E')
        return 1;

    maze[yPos][xPos] = '#';
    if (solveMazeDFS(maze, width, height, xPos + 1, yPos))
        return 1;
    if (solveMazeDFS(maze, width, height, xPos - 1, yPos))
        return 1;
    if (solveMazeDFS(maze, width, height, xPos, yPos + 1))
        return 1;
    if (solveMazeDFS(maze, width, height, xPos, yPos - 1))
        return 1;
    maze[yPos][xPos] = '.';
    return 0;
}

int checkMaze(char ** maze, int width, int height)
{
    int x = 0, y = 0;
    int prevX = x, prevY = y;
    while(x != width - 1 && y != height - 2)
    {
        printf("%d %d\n", x, y);
        printf("%d %d\n\n", prevX, prevY);

        if (y + 1 < height && maze[y + 1][x] == '#' && y + 1 != prevY)
        {
            if (y - 1 >= 0 && maze[y - 1][x] == '#' && y - 1 != prevY)
            {
                return 0; 
            }
            if (x + 1 < width && maze[y][x + 1] == '#' && x + 1 != prevX)
            {
                return 0; 
            }
            if (x - 1 >= 0 && maze[y][x - 1] == '#' && x - 1 != prevX)
            {
                return 0; 
            }
            prevY = y;
            prevX = x;
            y++;
        }
        else if (y - 1 >= 0 && maze[y - 1][x] == '#' && y - 1 != prevY)
        {
            if (y + 1 < height && maze[y + 1][x] == '#' && y + 1 != prevY)
            {
                return 0; 
            }
            if (x + 1 < width && maze[y][x + 1] == '#' && x + 1 != prevX)
            {
                return 0; 
            }
            if (x - 1 >= 0 && maze[y][x - 1] == '#' && x - 1 != prevX)
            {
                return 0; 
            }
            prevY = y;
            prevX = x;
            y--;
        }
        else if (x + 1 < width && maze[y][x + 1] == '#' && x + 1 != prevX)
        {
            if (y + 1 < height && maze[y + 1][x] == '#' && y + 1 != prevY)
            {
                return 0; 
            }
            if (y - 1 >= 0 && maze[y - 1][x] == '#' && y - 1 != prevY)
            {
                return 0; 
            }
            if (x - 1 >= 0 && maze[y][x - 1] == '#' && x - 1 != prevX)
            {
                return 0; 
            }
            prevX = x;
            prevY = y;
            x++;
        }
        else if (x - 1 >= 0 && maze[y][x - 1] == '#' && x - 1 != prevX)
        {
            if (y + 1 < height && maze[y + 1][x] == '#' && y + 1 != prevY)
            {
                return 0; 
            }
            if (y - 1 >= 0 && maze[y - 1][x] == '#' && y - 1 != prevY)
            {
                return 0; 
            }
            if (x + 1 < width && maze[y][x + 1] == '#' && x + 1 != prevX)
            {
                return 0; 
            }
            prevX = x;
            prevY = y;
            x--;
        }
        else
            {
                return 0; 
            }

    }
    return 1;
}