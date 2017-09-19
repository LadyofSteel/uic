/**
 *  @brief CS 211 Project 1
 *
 *  @author Ammar Subei
*/

typedef enum
{
  false,
  true
} bool;

/**
 *  @brief Struct for a stack object
*/
typedef struct Stack
{
  char *stack;  ///< Pointer to actual memory location
  int capacity; ///< Stack capacity
  int size;     ///< Stack size (used space)
} Stack;

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
void push(char symbol);

/**
 *  @brief Pops the stack
*/
bool pop();

/**
 *  @brief Gets top element from stack
*/
char top();

/**
 *  @brief Resets stack
*/
void resetStack();
