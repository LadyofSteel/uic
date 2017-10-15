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
*/
void doAdd(List *list);

/**
 *  @brief Sets new group as call-ahead
*/
void doCallAhead(List *list);

/**
 *  @brief Sets call-ahead group to waiting
*/
void doWaiting(List *list);

/**
 *  @brief Removes the first group from the waiting list
*/
void doRetrieve(List *list);

/**
 *  @brief Lists all groups after given group
*/
void doList(List *list);

/**
 *  @brief Displays all groups on the waiting list
*/
void doDisplay(List *list);

#endif /* COMMANDS_H */
