#include <stdio.h>
#include "maze.h"

/*
 * findStartEnd -- finds the x and y location of the start and end of the  maze
 *                 if the end or start does not exist should output (-1, -1) as the location
 * INPUTS:         maze -- 2D char array that holds the contents of the maze
 *                 width -- width of the maze
 *                 height -- height of the maze
 *                 xStart -- pointer to where x start location should be stored
 *                 yStart -- pointer to where y start location should be stored
 *                 xEnd -- pointer to where x end location should be stored
 *                 yEnd -- pointer to where y end location should be stored
 * OUTPUTS: xStart, yStart, xEnd, and yEnd set to corresponding locations
 * RETURN: none
 * SIDE EFFECTS: none
 */ 
void findStartEnd(char ** maze, int width, int height, int * xStart, int * yStart, int * xEnd, int * yEnd)
{
    int x, y;
    *xStart = -1;
    *yStart = -1;
    *xEnd = -1;
    *yEnd = -1;
    for(y = 0; y < height; y++)
    {
        for(x = 0; x < width; x++)
        {
            if (maze[y][x] == START) 
            {
                *xStart = x;
                *yStart = y;
            }
            if (maze[y][x] == END)
            {
                *xEnd = x;
                *yEnd = y;
            }
        }
    }
}

/*
 * printMaze -- prints out the maze in a human readable format (should look like examples)
 * INPUTS:      maze -- 2D char array that holds the contents of the maze 
 *              width -- width of the maze
 *              height -- height of the maze
 * OUTPUTS:     none
 * RETURN:      none
 * SIDE EFFECTS: prints the maze to the console
 */
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

int manhattan(int x1, int y1, int x2, int y2)
{
    int xDist = x1 - x2;
    int yDist = y1 - y2;
    if (xDist < 0) xDist *= -1;
    if (yDist < 0) yDist *= -1;
    return xDist + yDist;
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search and a manhattan distance heuristic
 * INPUTS:               maze -- 2D char array that holds the contents of the maze
 *                       width -- the width of the maze
 *                       height -- the height of the maze
 *                       xPos -- the current x position within the maze
 *                       yPos -- the current y position within the maze
 *                       xEnd -- the x position of the end of the maze
 *                       yEnd -- the y position of the end of the maze
 * OUTPUTS:              updates maze with the solution path ('.') and visited nodes ('~')
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         none
 */ 
int solveMazeManhattanDFS(char ** maze, int width, int height, int xPos, int yPos, int xEnd, int yEnd)
{
    if (xPos < 0 || xPos >= width || yPos < 0 || yPos >= height)
        return 0;
    if (maze[yPos][xPos] == WALL || maze[yPos][xPos] == PATH || maze[yPos][xPos] == VISITED)
        return 0;
    if (maze[yPos][xPos] == END)
        return 1;
 
    int start = 0;
    if (maze[yPos][xPos] == START)
        start = 1;
 
    maze[yPos][xPos] = PATH;

    int leftDist = manhattan(xPos - 1, yPos, xEnd, yEnd);
    int rightDist = manhattan(xPos + 1, yPos, xEnd, yEnd);
    int upDist = manhattan(xPos, yPos - 1, xEnd, yEnd);
    int downDist = manhattan(xPos, yPos + 1, xEnd, yEnd);

    int i;
    for(i = 0; i < 4; i++) 
    {
        if (leftDist <= rightDist && leftDist <= upDist && leftDist <= downDist) 
        {
            if (solveMazeManhattanDFS(maze, width, height, xPos - 1, yPos, xEnd, yEnd))
            {
                if (start)
                    maze[yPos][xPos] = START;
                return 1;    
            }
            leftDist = 1000000;
        }
        if (downDist <= upDist && downDist <= leftDist && downDist <= rightDist)
        {
            if (solveMazeManhattanDFS(maze, width, height, xPos, yPos + 1, xEnd, yEnd))
            {
                if (start)
                    maze[yPos][xPos] = START;
                return 1;    
            }
            downDist = 1000000;
        }
        if (rightDist <= leftDist && rightDist <= upDist && rightDist <= downDist)
        {            
            if (solveMazeManhattanDFS(maze, width, height, xPos + 1, yPos, xEnd, yEnd))
            {
                if (start)
                    maze[yPos][xPos] = START;
                return 1;    
            }
            rightDist = 1000000;
        }
        if (upDist <= leftDist && upDist <= rightDist && upDist <= downDist)
        {
            if (solveMazeManhattanDFS(maze, width, height, xPos, yPos - 1, xEnd, yEnd))
            {
                if (start)
                    maze[yPos][xPos] = START;
                return 1;    
            }
            upDist = 1000000;
        }
    }
 
    if (start)
        maze[yPos][xPos] = START;
    else
        maze[yPos][xPos] = VISITED;
 
    return 0;
}

int countSurroundingPath(char ** maze, int width, int height, int x, int y)
{
    int left = 0, right = 0, down = 0, up = 0;
    if ((x - 1) >= 0)
    {
        left = (maze[y][x - 1] == PATH) || (maze[y][x - 1] == START) || (maze[y][x - 1] == END);
    }
    if ((x + 1) < width)
    {
        right = (maze[y][x + 1] == PATH) || (maze[y][x + 1] == START) || (maze[y][x + 1] == END);
    }
    if ((y - 1) >= 0)
    {
        down = (maze[y - 1][x] == PATH) || (maze[y - 1][x] == START) || (maze[y - 1][x] == END);
    }
    if ((y + 1) < height)
    {
        up = (maze[y + 1][x] == PATH) || (maze[y + 1][x] == START) || (maze[y + 1][x] == END);
    }
    return left + right + down + up;
}

/*
 * checkMaze -- checks if a maze has a valid solution or not
 * INPUTS:      maze -- 2D char array that holds the contents of the maze
 *              width -- width of the maze
 *              height -- height of the maze
 *              x -- the starting x position in the maze
 *              y -- the starting y position in the maze
 * OUTPUTS:     none
 * RETURN:      1 if the maze has a valid solution, otherwise 0
 * SIDE EFFECTS: none
 */ 
int checkMaze(char ** maze, int width, int height, int x, int y)
{
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (maze[y][x] == START || maze[y][x] == END) {
                if (countSurroundingPath(maze, width, height, x, y) != 1)
                    return 0;
            }
            if (maze[y][x] == PATH) {
                if (countSurroundingPath(maze, width, height, x , y) != 2)
                    return 0;
            }
        }
    }
    return 1;
}

/*
 * solveMazeBFS -- solves the maze using a breadth first search algorithm
 * INPUTS:         maze -- A 2D array that contains the contents of the maze
 *                 width -- the width of the maze
 *                 height -- the height of the maze
 *                 xPos -- the starting x position within the maze
 *                 yPos -- the starting y position within the maze
 * OUTPUTS:        none
 * RETURNS:        0 if the maze is unsolvable, else 1
 * SIDE EFFECTS:   marks the cells within the maze as visited or part of the solution path
 */
int solveMazeBFS(char ** maze, int width, int height, int xPos, int yPos)
{
    int xHead = -1, xTail = -1, yHead = -1, yTail = -1;
    int xQueue[500];
    int yQueue[500];

    int parent[3000];

    enqueue(xQueue, xPos, &xHead, &xTail, 500);
    enqueue(yQueue, yPos, &yHead, &yTail, 500);
    int xCur, yCur;

    while ((xHead != xTail) && (yHead != yTail))
    {
        xCur = dequeue(xQueue, &xHead, &xTail, 500);
        yCur = dequeue(yQueue, &yHead, &yTail, 500);
        if (xCur == -1 || yCur == -1)
            return 0;

        if (maze[yCur][xCur] == END)
        {
            while (1)
            {
                int previous = parent[yCur * width + xCur];
                yCur = previous / width;
                xCur = previous % width;
                if (xCur == xPos && yCur == yPos)
                    break;
                maze[yCur][xCur] = PATH;   
            }
            return 1;
        }

        if (maze[yCur][xCur] != START)
            maze[yCur][xCur] = VISITED;

        int east = xCur + 1;
        int west = xCur - 1;
        int north = yCur - 1;
        int south = yCur + 1;

        if (west < width && (maze[yCur][west] == EMPTY || maze[yCur][west] == END))
        {
            enqueue(xQueue, west, &xHead, &xTail, 500);
            enqueue(yQueue, yCur, &yHead, &yTail, 500);
            parent[yCur * width + west] = yCur * width + xCur;
        }
        if (east >= 0 && (maze[yCur][east] == EMPTY || maze[yCur][east] == END))
        {
            enqueue(xQueue, east, &xHead, &xTail, 500);
            enqueue(yQueue, yCur, &yHead, &yTail, 500);
            parent[yCur * width + east] = yCur * width + xCur;
        }
        if (north >= 0 && (maze[north][xCur] == EMPTY || maze[north][xCur] == END))
        {
            enqueue(xQueue, xCur, &xHead, &xTail, 500);
            enqueue(yQueue, north, &yHead, &yTail, 500);
            parent[north * width + xCur] = yCur * width + xCur;
        }
        if (south < height && (maze[south][xCur] == EMPTY || maze[south][xCur] == END))
        {
            enqueue(xQueue, xCur, &xHead, &xTail, 500);
            enqueue(yQueue, south, &yHead, &yTail, 500);
            parent[south * width + xCur] = yCur * width + xCur;
        }
    }
     
    return 0;
}

/*
 * enqueue -- enqueues an integer onto the given queue
 * INPUTS:    queue -- a pointer to the array that will hold the contents of the queue
 *            value -- the value to  enqueue
 *            head -- a pointer to a variable that contains the head index in the queue
 *            tail -- a pointer to a variable that contains the tail index in the queue
 *            maxSize -- the maximum size of the queue (size of the array)
 * OUTPUTS:   none
 * RETURNS:   none
 * SIDE EFFECTS: adds an item to the queue
 */ 
void enqueue(int * queue, int value, int * head, int * tail, int maxSize)
{
    if ((*tail - maxSize) == *head)
    {
        printf("Queue is full\n");
        return;
    }
    *tail = *tail + 1;
    queue[*tail % maxSize] = value;
}

/* dequeue -- dequeues an item from the given queue
 * INPUTS:    queue -- a pointer to the array that holds the contents of the queue
 *            head -- a pointer to a variable that contains the head index in the queue
 *            tail -- a pointer to a variable that contains the tail index in the queue
 *            maxSize -- the maximum size of the queue (size of the array)
 * OUTPUTS:   none
 * RETURNS:   the value dequeued from the queue
 * SIDE EFFECTS: removes an item from the queue
 */
int dequeue(int * queue, int * head, int * tail, int maxSize)
{
    if (*head == *tail)
    {
        printf("Queue is empty\n");
        return -1;
    }
    *head = *head + 1;
    return queue[*head % maxSize];
}

