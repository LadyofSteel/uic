/**
 *  @brief Main file header
 *
 *  @author Ammar Subei
*/

#pragma once

#include "proj5Tokens.h"
#include "mystack.h"

/**
 *  @brief Checks for the debug flag
 *
 *  @param int argument count
 *  @param char** arguments array
*/
void checkDebug(const int argc, char *argv[]);

/**
 *  @brief Checks if the operator is arithmetic
 *
 *  In this context, an arithmetic operator is one of the following:
 *  + , - , * , /
 *
 *  @param char operator to check
 *  @return bool operator is arithmetic
*/
bool isArithmeticOperator(const char op);

/**
 *  @brief Checks if the operator is additive
 *
 *  In this context, an additive operator is one of the following:
 *  + , -
 *
 *  @param char operator to check
 *  @return bool operator is additive
*/
bool isAdditiveOperator(const char op);

/**
 *  @brief Checks if the operator is multiplicative
 *
 *  In this context, a multiplicative operator is one of the following:
 *  * , /
 *
 *  @param char operator to check
 *  @return bool operator is multiplicative
*/
bool isMultiplicativeOperator(const char op);

/**
 *  @brief Pops and evaluates the stacks
 *
 *  Given the operators and values stacks, this function pops the values
 *  and evaluates the result, which is then pushed into the values stack.
 *
 *  @param MyStack operators stack
 *  @param MyStack values stack
 *  @return bool evaluation successful
*/
bool popAndEvaluate(MyStack<char> &operator_stack, MyStack<int> &values_stack);

/**
 *  @brief Processes one expression
 *
 *  @param Token input token
 *  @param TokenReader* token reader
 *  @return bool processing successful
*/
bool processExpression(Token inputToken, TokenReader *tr);

/**
 *  @brief Prints the program commands
*/
void printCommands();
