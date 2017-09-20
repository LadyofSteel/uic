/**
 *  @brief CS 211 Project 2
 *
 *  @author Ammar Subei
*/

#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

void initStack(Stack *stack)
{
  stack->capacity = 2;
  stack->size = 0;
  stack->data = (char *) malloc(stack->capacity);
}

void resizeStack(Stack *stack)
{
  stack->capacity += 2;

  char *temp_data = (char *) malloc(stack->capacity);

  int i;
  for (i = 0; i < stack->size; i++)
    temp_data[i] = stack->data[i];

  (stack->data) = temp_data;
}

void resetStack(Stack *stack)
{
  free(stack->data);
  initStack(stack);
}

bool isEmpty(const Stack *stack)
{
  return ( stack->size == 0 );
}

bool isFull(const Stack *stack)
{
  return ( stack->size == stack->capacity );
}

void printStack(const Stack *stack)
{
  printf("Printing stack elements\n\n");

  int i;
  for (i = 0; i < stack->size; i++) {
    printf("Element %d: %c\n", i, stack->data[i]);
  }
}

void push(Stack *stack, const char symbol)
{
  if ( isFull(stack) )
    resizeStack(stack);

  stack->data[stack->size] = symbol;
  stack->size++;
}

bool pop(Stack *stack)
{
  if (stack->size <= 0)
    return false;

  stack->size--;
  return true;
}

char top(const Stack *stack)
{
  if ( !isEmpty(stack) )
    return ( stack->data[stack->size - 1] );

  return '0';
}
