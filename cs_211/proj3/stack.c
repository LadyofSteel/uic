/**
 *  @brief CS 211 Project 3
 *
 *  This file is used to define how the Stack object functions and is used.
 *
 *  @author Ammar Subei
*/

#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

Stack* createStack()
{
  Stack *new_stack = (Stack *) malloc( sizeof(Stack) );
  new_stack->head = NULL;

  return new_stack;
}

void cleanupStack(Stack *stack)
{
  StackNode *current = stack->head;

  while (current != NULL) {
    StackNode *temp = current;

    current = current->next;
    free(temp);
  }

  /*free(stack);*/
}

void resetStack(Stack *stack)
{
  cleanupStack(stack);
  stack = createStack();
}

bool isEmpty(const Stack *stack)
{
  return ( stack->head == NULL );
}

void printStack(const Stack *stack)
{
  // Allocated new memory to not alter the original stack
  Stack *temp = createStack();
  StackNode *current = stack->head;

  while (current != NULL) {
    push(temp, current->x_pos, current->y_pos);
    current = current->next;
  }

  printf("Printing stack elements\n\n");

  StackNode *temp_head = temp->head;
  while (temp_head != NULL) {
    printf("Position : (%d,%d)\n",
        temp_head->x_pos, temp_head->y_pos);

    temp_head = temp_head->next;
  }

  // Gotta free to avoid memory leaks
  cleanupStack(temp);
}

void push(Stack *stack, const int x, const int y)
{
  StackNode *new_node = (StackNode *) malloc( sizeof(StackNode) );
  new_node->x_pos = x;
  new_node->y_pos = y;
  new_node->next = stack->head;

  stack->head = new_node;
}

bool pop(Stack *stack)
{
  if ( isEmpty(stack) )
    return false;

  StackNode *temp = stack->head;
  stack->head = stack->head->next;

  free(temp);
  return true;
}

StackNode* top(const Stack *stack)
{
  if ( isEmpty(stack) )
    return NULL;

  return stack->head;
}
