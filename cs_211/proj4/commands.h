/**
 *  @brief CS 211 Project 4
 *
 *  This file is used for the commands.
 *
 *  @author Ammar Subei
*/

#ifndef COMMANDS_H
#define COMMANDS_H

#include "list.h"

/**
 *  @brief Adds new group
*/
void doAdd();

/**
 *  @brief Sets new group as call-ahead
*/
void doCallAhead();

/**
 *  @brief Sets call-ahead group to waiting
*/
void doWaiting();

/**
 *  @brief Removes the first group from the waiting list
*/
void doRetrieve();

/**
 *  @brief Lists all groups after given group
*/
void doList();

/**
 *  @brief Displays all groups on the waiting list
*/
void doDisplay();

#endif /* COMMANDS_H */
