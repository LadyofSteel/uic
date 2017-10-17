/**
 *  @brief CS 211 Project 4
 *
 *  This file implements the linked-list for the waiting list.
 *
 *  @author Patrick Troy
 *  @author Ammar Subei
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "interface.h"
#include "commands.h"
#include "list.h"

void clearToEoln()
{
  char ch;

  do {
    ch = getc(stdin);
  } while ((ch != '\n') && (ch != EOF));
}

char getNextNWSChar()
{
  char ch;
  ch = getc(stdin);

  if (ch == EOF || ch == '\n')
    return ch;

  while (isspace (ch)) {
    ch = getc(stdin);

    if (ch == EOF || ch == '\n')
      return ch;
  }

  return ch;
}

int getPosInt()
{
  int value = 0;

  // Clear white space characters
  int ch;
  ch = getc(stdin);
  while (!isdigit(ch)) {
    // Error \n ==> no integer given
    if ('\n' == ch)  
      return 0;

    // Error non white space ==> integer not given next
    if (!isspace(ch)) { 
      clearToEoln();
      return 0;
    }

    ch = getc(stdin);
  }

  value = ch - '0';
  ch = getc(stdin);

  while (isdigit(ch)) {
    value = value * 10 + ch - '0';
    ch = getc(stdin);
  }

  // Put the last read character back in input stream
  ungetc(ch, stdin); 

  // Integer value of 0 is an error in this program
  if (0 == value)
    clearToEoln();

  return value;
}

char* getName()
{
  // Skip over the white space characters
  int ch;
  ch = getc(stdin);

  while (isspace(ch)) {
    if ('\n' == ch)  // Error \n ==> no integer given
      return NULL;
    ch = getc(stdin);
  }

  char *word;
  int size;
  size = 10;
  word = (char *) malloc (sizeof(char) * size);

  // Read in character-by-character until the newline is encountered
  int count = 0;

  while (ch != '\n') {
    if (count + 1 >= size) {
      // Grow an array to make it "dynamically sized" using malloc
      char* temp;
      size = size * 2;
      temp = (char *) malloc ( sizeof(char) * size );

      printf ("Growing array from size %d to size %d\n", count, size);

      // Copy the characters to the new array
      int i;
      for (i = 0; i < count; i++)
        temp[i] = word[i];

      free(word);
      word = temp;
    }

    word[count] = ch;
    count++;
    word[count] = '\0';

    // Read next character
    ch = getc(stdin);
  }

  if (count > 30) {
    count = 30;
    word[count] = '\0';
  }

  // Clear ending white space characters
  while ( isspace(word[count-1]) ) {
    count--;
    word[count] = '\0';
  }

  return word;
}

void printCommands()
{
  printf("The commands for this program are:\n\n");
  printf("q - to quit the program\n");
  printf("? - to list the accepted commands\n");
  printf("a <size> <name> - to add a group to the wait list\n");
  printf("c <size> <name> - to add a call-ahead group to the wait list\n");
  printf("w <name> - to specify a call-ahead group is now waiting in the restaurant\n");
  printf("r <table-size> - to retrieve the first waiting group that can fit at the available table size\n");
  printf("l <name> - list how many groups are ahead of the named group\n");
  printf("d - display the wait list information\n");

  clearToEoln();
}

int main (int argc, char **argv)
{
  List *my_list = createList();
  bool debug_mode = false;
  int ch;

  if (argc > 1) {
    if ( !strcmp(argv[1], "-d") ) {
      debug_mode = true;
      printf("In debug mode!\n");
    }
  }

  printf("Starting Restaurant Wait List Program\n\n");
  printf("Enter command: ");

  while ((ch = getNextNWSChar()) != EOF) {
    // Check for the various commands
    if (ch == 'q') {
      printf("Quitting Program\n");
      return 0;
    } else if (ch == '?') {
      if (debug_mode)
        printf("DEBUG: Printing list of commands\n");

      printCommands();
    } else if (ch == 'a') {
      if (debug_mode)
        printf("DEBUG: Attempting to add group to waiting list\n");

      doAdd(my_list, debug_mode);
    } else if (ch == 'c') {
      if (debug_mode)
        printf("DEBUG: Attempting to add group as call-ahead\n");

      doCallAhead(my_list, debug_mode);
    } else if (ch == 'w') {
      if (debug_mode)
        printf("DEBUG: Changing call-ahead group to in-restaurant\n");

      doWaiting(my_list, debug_mode);
    } else if (ch == 'r') {
      if (debug_mode)
        printf("DEBUG: Attempting to retrieve a waiting group\n");

      doRetrieve(my_list, debug_mode);
    } else if (ch == 'l') {
      if (debug_mode)
        printf("DEBUG: Listing groups waiting ahead\n");

      doList(my_list, debug_mode);
    } else if (ch == 'd') {
      doDisplay(my_list, debug_mode);
    } else if (ch == '\n') {
      if (debug_mode)
        printf("DEBUG: No command was entered...\n");
    } else { // Nothing entered on input line
      printf("%c - in not a valid command\n", ch);
      printf("For a list of valid commands, type ?\n");
      clearToEoln();
    }

    printf("\nEnter command: ");
  }

  printf ("Quiting Program - EOF reached\n");
  return 1;
}
