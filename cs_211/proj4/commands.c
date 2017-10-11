#include "interface.h"

void doAdd()
{
  /* get group size from input */
  int size = getPosInt();
  if (size < 1) {
    printf ("Error: Add command requires an integer value of at least 1\n");
    printf ("Add command is of form: a <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }

  /* get group name from input */
  char *name = getName();
  if (name == NULL) {
    printf ("Error: Add command requires a name to be given\n");
    printf ("Add command is of form: a <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }

  printf ("Adding group \"%s\" of size %d\n", name, size);

  // add code to perform this operation here
}


void doCallAhead()
{
  /* get group size from input */
  int size = getPosInt();
  if (size < 1) {
    printf ("Error: Call-ahead command requires an integer value of at least 1\n");
    printf ("Call-ahead command is of form: c <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }

  /* get group name from input */
  char *name = getName();
  if (name == NULL)
  {
    printf ("Error: Call-ahead command requires a name to be given\n");
    printf ("Call-ahead command is of form: c <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }

  printf ("Call-ahead group \"%s\" of size %d\n", name, size);

  // add code to perform this operation here
}

void doWaiting()
{
  /* get group name from input */
  char *name = getName();
  if (name == NULL) {
    printf ("Error: Waiting command requires a name to be given\n");
    printf ("Waiting command is of form: w <name>\n");
    printf ("  where: <name> is the name of the group that is now waiting\n");
    return;
  }

  printf ("Waiting group \"%s\" is now in the restaurant\n", name);

  // add code to perform this operation here
}

void doRetrieve()
{
  /* get table size from input */
  int size = getPosInt();
  if (size < 1) {
    printf ("Error: Retrieve command requires an integer value of at least 1\n");
    printf ("Retrieve command is of form: r <size>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    return;
  }

  clearToEoln();
  printf ("Retrieve (and remove) the first group that can fit at a tabel of size %d\n", size);

  // add code to perform this operation here
}

void doList()
{
  /* get group name from input */
  char *name = getName();
  if (name == NULL) {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: l <name>\n");
    printf ("  where: <name> is the name of the group to inquire about\n");
    return;
  }

  printf ("Group \"%s\" is behind the following groups\n", name);

  // add code to perform this operation here
}

void doDisplay()
{
  clearToEoln();
  printf ("Display information about all groups\n");

  // add code to perform this operation here
}
