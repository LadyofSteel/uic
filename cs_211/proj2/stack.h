/**
 *  @brief CS 211 Project 2
 *
 *  @author Ammar Subei
*/

#ifndef STACK_H
#define STACK_H

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
  char *data;   ///< Pointer to actual data memory location
  int capacity; ///< Stack capacity
  int size;     ///< Stack size (used space)
} Stack;

/**
 *  @brief Initialize the stack
 *
 *  @param Stack object to initialize
*/
void initStack(Stack *stack);

/**
 *  @brief Resizes the stack
 *
 *  @param Stack object to resize
*/
void resizeStack(Stack *stack);

/**
 *  @brief Resets the stack
 *
 *  @param Stack object to reset
*/
void resetStack(Stack *stack);

/**
 *  @brief Checks if stack is empty
 *
 *  @param Stack object to check
 *  @return boolean stack is empty
*/
bool isEmpty(Stack *stack);

/**
 *  @brief Checks if stack is full
 *
 *  @param Stack object to check
 *  @return boolean stack is full
*/
bool isFull(Stack *stack);

/**
 *  @brief Pushes element onto stack
 *
 *  @param Stack object
 *  @param symbol character to push
*/
void push(Stack *stack, char symbol);

/**
 *  @brief Pops the stack
 *
 *  @param Stack object to pop
 *  @return boolean pop was successful
*/
bool pop(Stack *stack);

/**
 *  @brief Gets top element from stack
 *
 *  Access the top element from the given stack.
 *  If the stack is empty, it returns the character '0'.
 *
 *  @param Stack object
 *  @return symbol character at top of stack
*/
char top(Stack *stack);

#endif /* STACK_H */
