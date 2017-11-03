/**
 *  This file contains the user interface code for the Infix Evaluation Project
 *  Project 5 for CS 211 for Fall 2017
 *
 *  @date 10/21/17
 *  @author Patrick Troy
 *  @author Ammar Subei
*/

#include <iostream>

#include "asubei2proj5.h"

bool debug_mode = false;

void checkDebug(const int argc, char *argv[])
{
  if (argc == 2) {
    if ( !strcmp(argv[1], "-d") ) {
      debug_mode = true;
    }
  }
}

bool isArithmeticOperator(const char op)
{
  switch (op) {
    case '+' :
    case '-' :
    case '*' :
    case '/' : return true;
    default : return false;
  }
}

bool isAdditiveOperator(const char op)
{
  switch (op) {
    case '+' :
    case '-' : return true;
    default : return false;
  }
}

bool isMultiplicativeOperator(const char op)
{
  switch (op) {
    case '*' :
    case '/' : return true;
    default : return false;
  }
}

bool popAndEvaluate(MyStack<char> &operator_stack, MyStack<int> &values_stack)
{
  const char op = operator_stack.top();
  if (op == -1) {
    if (debug_mode) {
      std::cout << "ERROR: Trying to access empty operator stack!" << std::endl;
    }
    return false;
  }

  operator_stack.pop();

  const int value2 = values_stack.top();
  if (value2 == -1) {
    if (debug_mode) {
      std::cout << "ERROR: Trying to access empty values stack!" << std::endl;
    }
    return false;
  }

  values_stack.pop();

  const int value1 = values_stack.top();
  if (value1 == -1) {
    if (debug_mode) {
      std::cout << "ERROR: Trying to access empty values stack!" << std::endl;
    }
    return false;
  }

  values_stack.pop();

  int result = 0;
  if (op == '+') {
    result = value1 + value2;
  } else if (op == '-') {
    result = value1 - value2;
  } else if (op == '*') {
    result = value1 * value2;
  } else if (op == '/') {
    result = value1 / value2;
  } else {
    if (debug_mode) {
      std::cout << "ERROR: Operator is not arithmetic to evaluate!" << std::endl;
    }
    return false;
  } 

  values_stack.push(result);
  return true;
}

bool processExpression(Token inputToken, TokenReader *tr)
{
  MyStack<char> operator_stack;
  MyStack<int> values_stack;

  /* Loop until the expression reaches its end */
  while (inputToken.equalsType(EOLN) == false) {
    if (inputToken.equalsType(VALUE)) { // The expression contains a VALUE
      if (debug_mode)
        std::cout << "Value: " << inputToken.getValue() << std::endl;

      values_stack.push(inputToken.getValue());
    } else if (inputToken.equalsType(OPERATOR)) { // The expression contains an OPERATOR
      if (debug_mode) {
        std::cout << "Operator: " << inputToken.getOperator() << std::endl;
      }

      if (inputToken.getOperator() == '(') { // Operator is "("
        operator_stack.push(inputToken.getOperator());
      } else if ( isAdditiveOperator(inputToken.getOperator()) ) { // Operator is "+" or "-"
        while ( !operator_stack.isEmpty() && isArithmeticOperator(operator_stack.top()) ) {
          if ( !popAndEvaluate(operator_stack, values_stack) ) {
            return false;
          }
        }

        operator_stack.push(inputToken.getOperator());
      } else if ( isMultiplicativeOperator(inputToken.getOperator()) ) { // Operator is "*" or "/"
        while ( !operator_stack.isEmpty() && isMultiplicativeOperator(operator_stack.top()) ) {
          if ( !popAndEvaluate(operator_stack, values_stack) ) {
            return false;
          }
        }

        operator_stack.push(inputToken.getOperator());
      } else if (inputToken.getOperator() == ')') { // Operator is ")"
        while ( !operator_stack.isEmpty() && operator_stack.top() != '(' ) {
          if ( !popAndEvaluate(operator_stack, values_stack) ) {
            return false;
          }
        }

        if ( operator_stack.isEmpty() ) {
          if (debug_mode) {
            std::cout << "ERROR: Operator stack is empty!" << std::endl;
          }
          return false;
        } else {
          operator_stack.pop();
        }
      }
    }

    /* get next token from input */
    inputToken = tr->getNextToken ();
  }

  /* The expression has reached its end */

  while ( !operator_stack.isEmpty() ) {
    if ( !popAndEvaluate(operator_stack, values_stack) ) {
      return false;
    }
  }

  const int result = values_stack.top();
  if (result == -1) {
    if (debug_mode) {
      std::cout << "ERROR: Values stack is empty when getting the result!" << std::endl;
    }
    return false;
  }

  std::cout << "The expression evaluates to: " << result << std::endl;

  values_stack.pop();
  if ( !values_stack.isEmpty() ) {
    if (debug_mode) {
      std::cout << "ERROR: Values stack is not empty after evaluating the expression!" << std::endl;
    }
    return false;
  }

  std::cout << std::endl;
  return true;
}

void printCommands()
{
  std::cout << "The commands for this program are:" << std::endl << std::endl;
  std::cout << "q - to quit the program" << std::endl;
  std::cout << "? - to list the accepted commands" << std::endl;
  std::cout << "or any infix mathematical expression using operators of (), *, /, +, -" << std::endl;
}

int main(int argc, char *argv[])
{
  checkDebug(argc, argv);

  Token inputToken;
  TokenReader tr;

  std::cout << "Starting Expression Evaluation Program" << std::endl << std::endl;
  std::cout << "Enter Expression: ";

  inputToken = tr.getNextToken ();
  while (inputToken.equalsType(QUIT) == false) {
    /* check first Token on Line of input */
    if (inputToken.equalsType(HELP)) {
      printCommands();
      tr.clearToEoln();
    } else if (inputToken.equalsType(ERROR)) {
      std::cout << "Invalid Input - For a list of valid commands, type ?" << std::endl;
      tr.clearToEoln();
    } else if (inputToken.equalsType(EOLN)) {
      std::cout << "Blank Line - Do Nothing" << std::endl;
    } else {
      if ( !processExpression(inputToken, &tr) ) {
        std::cout << "Invalid infix expression!" << std::endl;
      }
    }

    std::cout << std::endl << "Enter Expression: ";
    inputToken = tr.getNextToken ();
  }

  std::cout << "Quitting Program" << std::endl;
  return 0;
}
