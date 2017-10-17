/**
 *  @brief CS 211 Project 4
 *
 *  This file is used to define the interface functions.
 *
 *  @author Ammar Subei
*/

#ifndef INTERFACE_H
#define INTERFACE_H

/**
 *  @brief Clear input until next EOL character
*/
void clearToEoln();

/**
 *  @brief Read in until the first non-white-space character
 *
 *  The white space characters are:
 *  space, tab \t, newline \n, vertical tab \v,
 *  form feed \f, and carriage return \r.
 *
 *  @return character input
*/
char getNextNWSChar();

/**
 *  @brief Read in a positive integer
 *
 *  Zero is not counted as a positive number,
 *
 *  @return positive integer input
*/
int getPosInt();

/**
 *  @brief Read in the name until the end of the input
 *
 *  @return string input name
*/
char* getName();

/**
 *  @brief Print out a list of the commands for this program
*/
void printCommands();

#endif /* INTERFACE_H */
