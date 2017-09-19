/**
 *  @brief CS 211 Project 2
 *
 *  @author Ammar Subei
*/

#ifndef MAIN_H
#define MAIN_H

#include "stack.h"

bool isSymbol(char input);

/**
 *  @brief Checks if stack is balanced
 *
 *  Checks if the given stack of symbols is balanced, and outputs the necessary
 *  messages to the user/stdout.
 *
 *  @param Stack object to check
 *  @return boolean stack is balanced
*/
bool checkBalanced(Stack stack);

void readline();

#endif /* MAIN_H */
