/**
 *  @brief CS 211 Project 2
 *
 *  @author Ammar Subei
*/

#include <stdlib.h>

#include "stack.h"

void initStack(Stack *stack)
{
  stack->capacity = 2;
  stack->size = 0;
  stack->data = (char *) malloc(sizeof(char) * stack->capacity);
}

void resizeStack(Stack *stack)
{
  stack->capacity += 2;

  char *temp_data = (char *) malloc(sizeof(char) * stack->capacity);

  int i;
  for (i = 0; i < stack->size; i++)
  {
    temp_data[i] = stack->data[i];
  }

  (stack->data) = temp_data;
}

void resetStack(Stack *stack)
{
}

bool isEmpty(Stack *stack)
{
  return ( stack->size == 0 );
}

bool isFull(Stack *stack)
{
  return ( stack->size == stack->capacity );
}

void push(Stack *stack, char symbol)
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

char top(Stack *stack)
{
  if ( !isEmpty(stack) )
    return ( stack->data[stack->size - 1] );

  return '0';
}
