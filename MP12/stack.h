#define MAXSIZE 100

/* A stack structure. Contains contents and an index to the top element */
struct stack {
	node * contents[MAXSIZE];
    int top;
};

/* Initializes the stack structure to be used */
void stackInit(stack * myStack);

/* Pushes an element onto the stack */
void stackPush(stack * myStack, node * element);

/* Pops an element off the stack */
node * stackPop(stack * myStack);