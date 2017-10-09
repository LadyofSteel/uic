/**
 *  @brief CS 211 Project 3
 *
 *  Main file header.
 *
 *  @author Ammar Subei
*/

#ifndef MAIN_H
#define MAIN_H

#include "stack.h"
#include "maze.h"

/**
 *  @brief Validates user input
 *
 *  Checks the arguments to the program and makes sure that
 *  and input file can be properly read. The order of arguments
 *  does not affect their validity.
 *
 *  @param int argument count
 *  @param char** arguments array
 *  @param FILE** mutable input file object
 *  @return boolean valid input
*/
bool validateInput(int arg_count, char **args, FILE **file);

/**
 *  @brief Reads info from file and builds maze
 *
 *  Reads the input file until EOF is encountered.
 *
 *  @param FILE pointer to input file
 *  @param Maze object pointer
*/
void readFile(FILE *file, Maze *maze);

#endif /* MAIN_H */
