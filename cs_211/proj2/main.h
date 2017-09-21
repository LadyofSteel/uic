/**
 *  @brief CS 211 Project 2
 *
 *  @author Ammar Subei
*/

#ifndef MAIN_H
#define MAIN_H

#include "stack.h"

/**
 *  @brief Checks if character is an open symbol
 *
 *  @param character to check
 *  @return bool character is open symbol
*/
bool isOpenSymbol(const char input);

/**
 *  @brief Checks if character is a close symbol
 *
 *  @param character to check
 *  @return bool character is close symbol
*/
bool isCloseSymbol(const char input);

/**
 *  @brief Gets the corresponding symbol
 *
 *  Gets the symbol character that corresponds to the input symbol.
 *  i.e getCorrespondingSymbol('{') returns '}'
 *
 *  @param input character symbol
 *  @return chararcter symbol corresponding to input
*/
char getCorrespondingSymbol(const char input);

/**
 *  @brief Checks if stack is balanced
 *
 *  @param Stack object to check
 *  @param character symbol to check against
 *  @return boolean stack is balanced
*/
bool checkBalanced(Stack *stack, const char symbol);

/**
 *  @brief Prints results for unbalanced expression
 *
 *  @param string message to print
 *  @param character symbol that would balance the expression
 *  @param integer position of unbalance
*/
void printUnbalanced(const char *message, const char symbol, const int position);

/**
 *  @brief Reads user input line
 *
 *  Reads one line from user (stdin) and updates the given stack accordingly. All results are
 *  handled in this function.
 *
 *  @param Stack object to update
*/
void processLine(Stack *stack);

/**
 *  @brief Cleans up allocated memory
 *
 *  @param Stack object to free
*/
void cleanup(Stack *stack);

#endif /* MAIN_H */
