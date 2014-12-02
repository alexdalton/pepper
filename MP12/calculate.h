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

/* Creates an expression tree and parses it to evaluate the postfix expression */
void postfix(char * exp_str);

/* Converts an infix expression to a postfix expression, creates an expression tree,
   and parses it to evaluate the expression */
void infix(char * exp_str;)