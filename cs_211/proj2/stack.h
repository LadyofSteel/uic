/**
 *  @brief CS 211 Project 1
 *
 *  @author Ammar Subei
*/

typedef enum { false, true } bool;

typedef struct Stack
{
  char *stack;
  int capacity;
  int top;
} Stack;

typedef union
{
  char symbol;
} Symbol;

/**
 *  @brief Initialize the stack
*/
void initStack();

/**
 *  @brief Checks if stack is empty
*/
bool isEmpty(Stack stack);

/**
 *  @brief Pushes element onto stack
*/
void push(Symbol symbol);

/**
 *  @brief Pops the stack
*/
bool pop();

/**
 *  @brief Gets top element from stack
*/
Symbol top();

/**
 *  @brief Resets stack
*/
void resetStack();
