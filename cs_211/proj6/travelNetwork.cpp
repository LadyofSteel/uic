/**
 *  @brief TravelNetwork definitions
 *
 *  @author Ammar Subei
 */

#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "travelNetwork.h"

TravelNetwork::TravelNetwork()
{
}

void TravelNetwork::initAirports()
{
  if (!airports.isEmpty()) {
    airports.removeAll();
  }

  for (int i = 1; i < 11; i++) {
    Airport newAirport = Airport(i, false);
    airports.add(newAirport);
  }
}

void TravelNetwork::initAirports(const int numAirports)
{
  if (!airports.isEmpty()) {
    airports.removeAll();
  }

  for (int i = 1; i <= numAirports; i++) {
    Airport newAirport = Airport(i, false);
    airports.add(newAirport);
  }
}

void TravelNetwork::processCommandLoop(FILE *inFile)
{
  char buffer[300];
  char* input;

  input = fgets( buffer, 300, inFile ); // get a line of input

  // loop until all lines are read from the input
  while (input != NULL) {
    // process each line of input using the strtok functions 
    char* command;
    command = strtok (input , " \n\t");

    printf ("*%s*\n", command);

    if ( command == NULL )
      printf ("Blank Line\n");
    else if ( strcmp (command, "q") == 0) 
      exit(0);
    else if ( strcmp (command, "?") == 0) 
      showCommands();
    else if ( strcmp (command, "t") == 0) 
      doTravel();
    else if ( strcmp (command, "r") == 0) 
      doResize();
    else if ( strcmp (command, "i") == 0) 
      doInsert();
    else if ( strcmp (command, "d") == 0) 
      doDelete();
    else if ( strcmp (command, "l") == 0) 
      doList();
    else if ( strcmp (command, "f") == 0) 
      doFile();
    else if ( strcmp (command, "#") == 0) 
      ; // Do nothing
    else
      printf ("Command is not known: %s\n", command);

    input = fgets ( buffer, 300, inFile );   // get the next line of input
  }
}

void TravelNetwork::showCommands()
{
  printf("The commands for this project are:\n");
  printf("  q \n");
  printf("  ? \n");
  printf("  # \n");
  printf("  t <int1> <int2> \n");
  printf("  r <int> \n");
  printf("  i <int1> <int2> \n");
  printf("  d <int1> <int2> \n");
  printf("  l \n");
  printf("  f <filename> \n");
}

void TravelNetwork::doTravel()
{
  int val1 = 0;
  int val2 = 0;

  // get an integer value from the input
  char* next = strtok (NULL, " \n\t");
  if ( next == NULL ) {
    printf ("Integer value expected\n");
    return;
  }

  val1 = atoi ( next );
  if ( val1 == 0 && strcmp (next, "0") != 0) {
    printf ("Integer value expected\n");
    return;
  }

  // get another integer value from the input
  next = strtok (NULL, " \n\t");
  if ( next == NULL ) {
    printf ("Integer value expected\n");
    return;
  }

  val2 = atoi ( next );
  if ( val2 == 0 && strcmp (next, "0") != 0) {
    printf ("Integer value expected\n");
    return;
  }

  printf ("Performing the Travel Command from %d to %d\n", 
      val1, val2);
}

void TravelNetwork::doResize()
{
  int val1 = 0;

  char* next = strtok (NULL, " \n\t");
  if ( next == NULL ) {
    printf ("Integer value expected\n");
    return;
  }

  val1 = atoi ( next );
  if ( val1 == 0 && strcmp (next, "0") != 0) {
    printf ("Integer value expected\n");
    return;
  }

  printf ("Performing the Resize Command with %d\n", val1 );

  initAirports(val1);
}

void TravelNetwork::doInsert()
{
}

void TravelNetwork::doDelete()
{
}

void TravelNetwork::doList()
{
}

void TravelNetwork::doFile()
{
  // get a filename from the input
  char* fname = strtok(NULL, " \n\t");
  if ( fname == NULL ) {
    printf ("Filename expected\n");
    return;
  }

  printf ("Performing the File command with file: %s\n", fname);

  // next steps:  (if any step fails: print an error message and return ) 
  //  1. verify the file name is not currently in use
  //  2. open the file using fopen creating a new instance of FILE*
  //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
  //  4. close the file when processCommandLoop() returns
}
