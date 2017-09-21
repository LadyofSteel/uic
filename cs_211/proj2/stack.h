/**
 *  @brief CS 211 Project 2
 *
 *  This file is used to create and use a stack object.
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
bool isEmpty(const Stack *stack);

/**
 *  @brief Checks if stack is full
 *
 *  @param Stack object to check
 *  @return boolean stack is full
*/
bool isFull(const Stack *stack);

/**
 *  @brief Prints out all stack elements
 *
 *  @param Stack object to print out
*/
void printStack(const Stack *stack);

/**
 *  @brief Pushes element onto stack
 *
 *  @param Stack object
 *  @param symbol character to push
*/
void push(Stack *stack, const char symbol);

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
char top(const Stack *stack);

#endif /* STACK_H */
