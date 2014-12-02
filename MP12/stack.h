#define MAXSIZE 100

/* A tree node that makes up the expression tree
   item - the item (operand or value) for this node
   left - pointer to left node
   right - pointer to right node
*/
struct node {
	char item;
	node * left;
	node * right;
};

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
