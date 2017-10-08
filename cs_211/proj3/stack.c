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

void initStack(Stack *stack)
{
  stack = (Stack *) malloc( sizeof(Stack) );
  stack->head = NULL;
}

void resetStack(Stack *stack)
{
  StackNode *current = stack->head;

  while (current != NULL) {
    StackNode *temp = current;

    current = current->next;
    free(temp);
  }

  initStack(stack);
}

bool isEmpty(const Stack *stack)
{
  return ( stack->head == NULL );
}

void printStack(const Stack *stack)
{
  // Allocated new memory to not alter the original stack
  StackNode *current = (StackNode *) malloc( sizeof(StackNode) );
  current = stack->head;

  printf("Printing stack elements\n\n");

  while (current != NULL) {
    printf("Position : (%d,%d) -- visited : %d\n",
        current->x_pos, current->y_pos, current->is_visited);

    current = current->next;
  }

  // Gotta free to avoid memory leaks
  free(current);
}

void push(Stack *stack, const int x, const int y)
{
  StackNode *newNode = (StackNode *) malloc( sizeof(StackNode) );
  newNode->is_visited = false;
  newNode->x_pos = x;
  newNode->y_pos = y;
  newNode->next = stack->head;

  stack->head = newNode;
}

bool pop(Stack *stack)
{
  if ( isEmpty(stack) )
    return false;

  StackNode *current = stack->head;
  StackNode *temp = current;

  current = current->next;

  free(temp);
  return true;
}

StackNode* top(const Stack *stack)
{
  if ( isEmpty(stack) )
    return NULL;

  return stack->head;
}
