#define MAXSIZE 100

typedef struct node {
    int value;
    struct node * left;
    struct node * right;
} node;

struct stack {
    int contents[MAXSIZE];
    int top;
};

