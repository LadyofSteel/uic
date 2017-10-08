/**
 *  @brief CS 211 Project 3
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
 *  @brief StructNode for each stack element
*/
typedef struct StackNode
{
  int x_pos;              //!< Integer value for x position
  int y_pos;              //!< Integer value for y position
  struct StackNode *next; //!< Pointer to the next StackNode object
} StackNode;

/**
 *  @brief Struct for a stack object
*/
typedef struct Stack
{
  StackNode *head; //!< Pointer to the head of the stack
} Stack;

/**
 *  @brief Initialize the stack
 *
 *  @param Stack object to initialize
*/
void initStack(Stack *stack);

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
 *  @brief Prints out all stack elements
 *
 *  @param Stack object to print out
*/
void printStack(const Stack *stack);

/**
 *  @brief Pushes coordinates onto stack
 *
 *  @param Stack object
 *  @param integer value for x position
 *  @param integer value for y position
*/
void push(Stack *stack, const int x, const int y);

/**
 *  @brief Pops the stack
 *
 *  @param Stack object to pop
 *  @return boolean pop was successful
*/
bool pop(Stack *stack);

/**
 *  @brief Gets top node from stack
 *
 *  Access the top node from the given stack.
 *  If the stack is empty, it returns NULL.
 *
 *  @param Stack object
 *  @return top StackNode object
*/
StackNode* top(const Stack *stack);

#endif /* STACK_H */
