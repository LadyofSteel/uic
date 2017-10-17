/**
 *  @brief CS 211 Project 4
 *
 *  This file implements the commands.
 *
 *  @author Ammar Subei
*/

#include "commands.h"

void doAdd(List *list, bool debug)
{
  // Get group size from input
  int size = getPosInt();
  if (size < 1) {
    printf("Error: Add command requires an integer value of at least 1\n");
    printf("Add command is of form: a <size> <name>\n");
    printf("  where: <size> is the size of the group making the reservation\n");
    printf("         <name> is the name of the group making the reservation\n");
    return;
  }

  // Get group name from input
  char *name = getName();
  if (name == NULL) {
    printf("Error: Add command requires a name to be given\n");
    printf("Add command is of form: a <size> <name>\n");
    printf("  where: <size> is the size of the group making the reservation\n");
    printf("         <name> is the name of the group making the reservation\n");
    return;
  }

  if ( doesNameExist(list, name) ) {
    printf("ERROR: group name %s already exists!\n", name);
    return;
  }

  printf("Adding group \"%s\" of size %d\n", name, size);
  addToList(list, name, size, true, debug);
}

void doCallAhead(List *list, bool debug)
{
  // Get group size from input
  int size = getPosInt();
  if (size < 1) {
    printf("Error: Call-ahead command requires an integer value of at least 1\n");
    printf("Call-ahead command is of form: c <size> <name>\n");
    printf("  where: <size> is the size of the group making the reservation\n");
    printf("         <name> is the name of the group making the reservation\n");
    return;
  }

  // Get group name from input
  char *name = getName();
  if (name == NULL) {
    printf("Error: Call-ahead command requires a name to be given\n");
    printf("Call-ahead command is of form: c <size> <name>\n");
    printf("  where: <size> is the size of the group making the reservation\n");
    printf("         <name> is the name of the group making the reservation\n");
    return;
  }

  if ( doesNameExist(list, name) ) {
    printf("ERROR: group name %s already exists!\n", name);
    return;
  }

  printf("Adding call-ahead group \"%s\" of size %d\n", name, size);
  addToList(list, name, size, false, debug);
}

void doWaiting(List *list, bool debug)
{
  // Get group name from input
  char *name = getName();
  if (name == NULL) {
    printf("Error: Waiting command requires a name to be given\n");
    printf("Waiting command is of form: w <name>\n");
    printf("  where: <name> is the name of the group that is now waiting\n");
    return;
  }

  if ( !doesNameExist(list, name) ) {
    printf("ERROR: group %s is not in the waiting list\n", name);
    return;
  }

  if ( !updateStatus(list, name, true, debug) ) {
    printf("ERROR: group %s is already waiting in the restaurant.\n", name);
    return;
  }

  printf("Waiting group \"%s\" is now in the restaurant\n", name);
}

void doRetrieve(List *list, bool debug)
{
  // Get table size from input
  int size = getPosInt();
  if (size < 1) {
    printf("Error: Retrieve command requires an integer value of at least 1\n");
    printf("Retrieve command is of form: r <size>\n");
    printf("  where: <size> is the size of the group making the reservation\n");
    return;
  }

  clearToEoln();
  printf("Retrieve (and remove) the first group that can fit at a tabel of size %d\n", size);

  char *group_name = retrieveAndRemove(list, size, debug);
  
  if (group_name == NULL) {
    printf("ERROR: could not find group of size %d or smaller waiting in restaurant\n", size);
    return;
  }

  printf("Successfully retrieved group %s.\n", group_name);
  free(group_name);
}

void doList(List *list, bool debug)
{
  // Get group name from input
  char *name = getName();
  if (name == NULL) {
    printf("Error: List command requires a name to be given\n");
    printf("List command is of form: l <name>\n");
    printf("  where: <name> is the name of the group to inquire about\n");
    return;
  }

  if ( !doesNameExist(list, name) ) {
    printf("ERROR: group %s is not in the waiting list\n", name);
    return;
  }

  int group_count = countGroupsAhead(list, name, debug);
  printf("Group \"%s\" is behind %d groups\n", name, group_count);

  displayGroupSizeAhead(list, name, debug);
}

void doDisplay(List *list, bool debug)
{
  clearToEoln();
  printf("Displaying information about all groups\n");

  displayListInformation(list, debug);
}
