#define WALL    '%'
#define EMPTY   ' '
#define START   'S'
#define END     'E'
#define PATH    '.'
#define VISITED '~'

// These functions must be implemented correctly for full functionality points 
void findStart(char ** maze, int width, int height, int * x, int * y);
void printMaze(char ** maze, int width, int height);
int solveMazeDFS(char ** maze, int width, int height, int xPos, int yPos);
int checkMaze(char ** maze, int width, int height, int x, int y);

// This function must be implemented correctly for full challenge points
int solveMazeBFS(char ** maze, int width, int height, int xPos, int yPos);

// Queue functions that might be helpful for the challenge
void enqueue(int * queue, int value, int * head, int * tail, int maxSize);
int dequeue(int * queue, int * head, int * tail, int maxSize);
