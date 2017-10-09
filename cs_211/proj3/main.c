#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "maze.h"
#include "stack.h"

bool is_debug = false;  //!< Global variable for debugging messages

/* verify the proper number of command line arguments were given */
bool validateInput(int arg_count, char **args, FILE **file)
{
  if (arg_count < 2) {  // No input arguments
    fprintf(stderr, "Invalid input! Correct usage: %s <input file name>\n", args[0]);
    return false;
  } else if (arg_count == 2) {
    if ( !strcmp(args[1], "-d") ) { // Only '-d' flag input
      fprintf(stderr, "Invalid input! Correct usage: %s <input file name>\n", args[0]);
      return false;
    }

    *file = fopen(args[1], "r");
    if (*file == NULL) {
      fprintf (stderr, "ERROR: Cannot open input file: %s", args[1] );
      return false;
    }
  } else if(arg_count == 3) {  // Input file and '-d' flag
    // Must correctly read input file
    if ( !strcmp(args[1], "-d") ) {
      is_debug = true;
      *file = fopen(args[2], "r");
    } else if ( !strcmp(args[2], "-d") ) {
      is_debug = true;
      *file = fopen(args[1], "r");
    }

    if (*file == NULL) {
      fprintf (stderr, "ERROR: Cannot open input file.");
      return false;
    }
  } else {  // Too many arguments
      fprintf(stderr, "Too many arguments given. Aborting...");
      return false;
  }

  if (is_debug)
    printf("DEBUG: User input is valid. Cross your fingers!\n");
  return true;
}

void readFile(FILE *file, Maze *maze)
{
  if (is_debug)
    printf("DEBUG: Attempting to read input file now.\n");

  // Read maze size
  int rows = 0;
  int cols = 0;
  while (rows < 1 || cols < 1) {
    fscanf(file, "%d %d", &rows, &cols);
  }
  initMazeSize(maze, rows, cols);

  if (is_debug)
    printf("DEBUG: Maze size has been initialized.\n");

  // Read start position
  rows = 0;
  cols = 0;
  while (rows < 1 ||
      cols < 1 ||
      rows > maze->rows ||
      cols > maze->columns) {
    fscanf(file, "%d %d", &rows, &cols);
  }
  maze->x_start = rows;
  maze->y_start = cols;

  if (is_debug)
    printf("DEBUG: Start position recorded (%d,%d).\n", rows, cols);

  // Read end position
  rows = 0;
  cols = 0;
  while (rows < 1 ||
      cols < 1 ||
      rows > maze->rows ||
      cols > maze->columns) {
    fscanf(file, "%d %d", &rows, &cols);
  }
  maze->x_end = rows;
  maze->y_end = cols;

  if (is_debug)
    printf("DEBUG: End position recorded (%d,%d).\n", rows, cols);

  initMaze(maze);

  if (is_debug)
    printf("DEBUG: Maze has been setup. Proceeding to mark blocked positions.\n");

  // Mark blocked positions with "*"s
  rows = 0;
  cols = 0;
  while ( fscanf(file, "%d %d", &rows, &cols) != EOF ) {
      if ((rows >= 1 && cols >= 1) &&
          (rows != maze->x_start || cols != maze->y_start) &&
          (rows != maze->x_end || cols != maze->y_end) &&
          (rows <= maze->rows && cols <= maze->columns)) {
        maze->data[rows][cols].symbol = '*';
      }
  }

  if (is_debug)
    printf("DEBUG: Maze successfully setup and ready to roll!\n");
}

bool getNeighbors(Maze *maze, Stack *stack, const int row, const int col)
{
  bool has_neighbors = false;
  int new_row = row + 1;
  int new_col = col;

  if (new_row >= 1 &&
      new_col >= 1 &&
      new_row <= maze->rows &&
      new_col <= maze->columns) {
    if ( !isVisited(maze, new_row, new_col) ) {
      if ( !isBlocked(maze, new_row, new_col) ) {
        push(stack, new_row, new_col);
        markVisited(maze, new_row, new_col);
        has_neighbors = true;
      }
    }
  }

  new_row = row - 1;
  new_col= col;
  if (new_row >= 1 &&
      new_col >= 1 &&
      new_row <= maze->rows &&
      new_col <= maze->columns) {
    if ( !isVisited(maze, new_row, new_col) ) {
      if ( !isBlocked(maze, new_row, new_col) ) {
        push(stack, new_row, new_col);
        markVisited(maze, new_row, new_col);
        has_neighbors = true;
      }
    }
  }

  new_row = row;
  new_col= col + 1;
  if (new_row >= 1 &&
      new_col >= 1 &&
      new_row <= maze->rows &&
      new_col <= maze->columns) {
    if ( !isVisited(maze, new_row, new_col) ) {
      if ( !isBlocked(maze, new_row, new_col) ) {
        push(stack, new_row, new_col);
        markVisited(maze, new_row, new_col);
        has_neighbors = true;
      }
    }
  }

  new_row = row;
  new_col= col - 1;
  if (new_row >= 1 &&
      new_col >= 1 &&
      new_row <= maze->rows &&
      new_col <= maze->columns) {
    if ( !isVisited(maze, new_row, new_col) ) {
      if ( !isBlocked(maze, new_row, new_col) ) {
        push(stack, new_row, new_col);
        markVisited(maze, new_row, new_col);
        has_neighbors = true;
      }
    }
  }

  return has_neighbors;
}

bool solveMaze(Maze *maze, Stack *stack)
{
  if (is_debug)
    printf("DEBUG: Attempting to solve maze now.\n");

  push(stack, maze->x_start, maze->y_start);
  markVisited(maze, maze->x_start, maze->y_start);

  while ( !isEmpty(stack) ) {
    StackNode *current_node = top(stack);
    int current_row = current_node->x_pos;
    int current_col = current_node->y_pos;

    if (current_node->x_pos == maze->x_end &&
        current_node->y_pos == maze->y_end) {
      // End has been reached
      break;
    }

    if ( !getNeighbors(maze, stack, current_row, current_col) ) {
      pop(stack);
    }
  }

  if ( isEmpty(stack) )
    return false;
  else
    return true;
}

int main (int argc, char **argv)
{
  FILE *in_file = NULL;
  
  if (!validateInput(argc, argv, &in_file)) {
    printf("Goodbye!\n");
    return -1;
  }

  if (is_debug)
    printf("DEBUG: In debug mode!\n");

  Maze *my_maze = createMaze();
  Stack *my_stack = createStack();

  readFile(in_file, my_maze);

  if (is_debug)
    printf("DEBUG: Finished reading file. Printing maze now.\n");

  printMaze(my_maze);

  if ( solveMaze(my_maze, my_stack) ) {
    printStack(my_stack);
  } else {
    printf("The input maze has no solution!\n");
    printf("Try a different maze next time.\n");
  }

  printf("\nGoodbye!\n");
}
