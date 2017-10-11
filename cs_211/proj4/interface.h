/**
 *  @brief CS 211 Project 4
 *
 *  This file is used to create and use a linked-list
 *  as a queue object.
 *
 *  @author Ammar Subei
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
  false,
  true
} bool;

/* Clear input until next End of Line Character - \n */
void clearToEoln();

/* Read in until the first Non-White-Space character is Read */
/* The white space characters are:
*      space, tab \t, newline \n, vertical tab \v, 
*      form feed \f, and carriage return \r
*/ 
int getNextNWSChar ();

/* read in the next Positive Integer or error:    */
/* This is based on the Mathematical definition of a Postive Integer */
/*    zero is not counted as a positive number */ 
int getPosInt ();

/* read in the name until the end of the input */
char *getName();

/* Print out a list of the commands for this program */
void printCommands();

#endif /* INTERFACE_H */
