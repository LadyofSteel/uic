/**
 *  @brief CS 211 Project 4
 *
 *  This file is used for the commands.
 *
 *  @author Ammar Subei
*/

#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "interface.h"

/**
 *  @brief Adds new group
 *
 *  @param List object
 *  @param bool in debug mode
*/
void doAdd(List *list, bool debug);

/**
 *  @brief Sets new group as call-ahead
 *
 *  @param List object
 *  @param bool in debug mode
*/
void doCallAhead(List *list, bool debug);

/**
 *  @brief Sets call-ahead group to waiting
 *
 *  @param List object
 *  @param bool in debug mode
*/
void doWaiting(List *list, bool debug);

/**
 *  @brief Removes the first group from the waiting list
 *
 *  @param List object
 *  @param bool in debug mode
*/
void doRetrieve(List *list, bool debug);

/**
 *  @brief Lists all groups after given group
 *
 *  @param List object
 *  @param bool in debug mode
*/
void doList(List *list, bool debug);

/**
 *  @brief Displays all groups on the waiting list
 *
 *  @param List object
 *  @param bool in debug mode
*/
void doDisplay(List *list, bool debug);

#endif /* COMMANDS_H */
