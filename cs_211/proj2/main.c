/**
 *  @brief CS 211 Project 2
 *
 *  Main source file that defines all functions and uses the stack to implement the 
 *  program defined for class. The Stack object is used to check if a given expression
 *  has balanced open/close symbols.
 *
 *  @author Ammar Subei
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "stack.h"

// Global variable for debug mode
bool debug_mode = false;

bool isOpenSymbol(const char input)
{
  const char *open_symbols = "({[<";

  if ( strchr(open_symbols, input) ) // strchr finds first occurrence of char in string
    return true;

  return false;
}

bool isCloseSymbol(const char input)
{
  const char *close_symbols = ")}]>";

  if ( strchr(close_symbols, input) ) // strchr finds first occurrence of char in string
    return true;

  return false;
}

char getCorrespondingSymbol(const char input)
{
  const char *opening_symbols = "({[<";
  const char *closing_symbols = ")}]>";

  const char *open_symbol_location = strchr(opening_symbols, input);
  const char *close_symbol_location = strchr(closing_symbols, input);

  if (open_symbol_location) {
    int index = open_symbol_location - opening_symbols;
    return closing_symbols[index];
  } else {
    int index = close_symbol_location - closing_symbols;
    return opening_symbols[index];
  }
}

bool checkBalanced(Stack *stack, const char symbol)
{
  if ( top(stack) == getCorrespondingSymbol(symbol) ) {
    if (debug_mode)
      printf("\nDEBUG: Popping the stack, top symbol was %c\n", top(stack));

    pop(stack);
    return true;
  } else {
    return false;
  }
}

void printUnbalanced(const char* message, const char symbol, const int position)
{
  int i;
  for (i = 0; i < position; i++)
    printf(" ");

  printf("^ %s %c\n", message, symbol);
}

void readInput(Stack *stack)
{
  int input_size;
  char *input;
  while (true) {
    input_size = 300;
    input = (char *) malloc(input_size);

    printf("\nPlease enter an expression\n");

    // Read one line from stdin
    fgets(input, input_size, stdin);
    // Strip EOL char(s)
    input[strcspn(input, "\r\n")] = '\0';
    // Update input size accordingly
    input_size = strlen(input);

    if ( !strcmp(input, "Q") || !strcmp(input, "q") )
      break;

    if (debug_mode)
      printf("\nDEBUG: Processing your input\n");

    processLine(input, stack);

    if (debug_mode)
      printf("\nDEBUG: Resetting the stack\n");

    resetStack(stack);
  }

  free(input);
  printf("No more? Alright...\n");
}

void processLine(char *input_line, Stack *stack)
{
  int input_size = strlen(input_line);

  int i;
  for (i = 0; i < input_size; i++) {
    // Only push an open symbol character
    if ( isOpenSymbol(input_line[i]) ) {
      if (debug_mode)
        printf("\nDEBUG: Pushing symbol %c into the stack\n", input_line[i]);

      push(stack, input_line[i]);
    } else if ( isCloseSymbol(input_line[i]) ) {
      if ( !checkBalanced(stack, input_line[i]) )
        break;
    }
  }

  printf("You entered the expression:\n");
  printf("%s\n", input_line);
  
  if (i == input_size) {
    if (!isEmpty(stack)) {
      // If we went through the expression but missing closing symbols
      const char missing_symbol = getCorrespondingSymbol(top(stack));
      printUnbalanced("missing symbol", missing_symbol, i);
    } else {
      // If we went through the expression with no issues
      printf("Expression is balanced! Way to go!\n");
    }
  } else if (isEmpty(stack)) {
    // If stack was empty in the middle of the expression
    const char missing_symbol = getCorrespondingSymbol(input_line[i]);
    printUnbalanced("missing symbol", missing_symbol, i);
  } else {
    // If closing symbol was the wrong one
    const char missing_symbol = getCorrespondingSymbol(top(stack));
    printUnbalanced("expecting symbol", missing_symbol, i);
  }
}

void cleanup(Stack *stack)
{
  if (debug_mode)
    printf("\nDEBUG: Cleaning up the mess\n");

  free(stack->data);
  free(stack);
}

int main(int argc, char *argv[])
{
  // First check if we're running in debug mode
  if (argc > 1) {
    if (!strcmp(argv[1], "-d"))
        debug_mode = true;
  }

  // Initialize the stack
  Stack *stack = (Stack *) malloc(sizeof(Stack));
  initStack(stack);

  // Read user input until "q" or "Q" is entered
  readInput(stack);

  // Clean up the mess
  cleanup(stack);

  printf("Goodbye\n");

  // Kaboom
  return 0;
}
