/**
 *  @brief CS 211 Project 2
 *
 *  @author Ammar Subei
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "stack.h"

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
      printf("Popping the stack, top symbol was %c\n", top(stack));

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

void readline(Stack *stack)
{
  int input_size = 300;
  char *input = (char *) malloc(input_size);

  fgets(input, input_size, stdin);
  input[strcspn(input, "\r\n")] = '\0'; // strip EOL char(s)

  input_size = strlen(input);

  int i;
  for (i = 0; i < input_size; i++) {
    // Only push an open symbol character
    if ( isOpenSymbol(input[i]) ) {
      if (debug_mode)
        printf("Pushing symbol %c into the stack\n", input[i]);

      push(stack, input[i]);
    } else if ( isCloseSymbol(input[i]) ) {
      if ( !checkBalanced(stack, input[i]) )
        break;
    }
  }

  printf("You entered the expression:\n");
  printf("%s\n", input);
  
  if (i == input_size) {
    if (!isEmpty(stack)) {
      const char missing_symbol = getCorrespondingSymbol(top(stack));
      printUnbalanced("missing symbol", missing_symbol, i);
    } else {
      printf("Expression is balanced! Way to go!\n");
    }
  } else if (isEmpty(stack)) {
    const char missing_symbol = getCorrespondingSymbol(input[i]);
    printUnbalanced("missing symbol", missing_symbol, i);
  } else {
    const char missing_symbol = getCorrespondingSymbol(input[i]);
    printUnbalanced("expecting symbol", missing_symbol, i);
  }
}

int main(int argc, char *argv[])
{
  if (argc > 1) {
    if (!strcmp(argv[1], "-d"))
        debug_mode = true;
  }

  Stack *stack = (Stack *) malloc(sizeof(Stack));

  initStack(stack);

  readline(stack);

  return 0;
}
