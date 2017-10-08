#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "maze.h"
#include "stack.h"

bool is_debug = false;

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

  return true;
}

void readInput(FILE *file, Maze *maze)
{
  // Read maze size
  int rows = 0;
  int cols = 0;
  while (rows < 1 || cols < 1) {
    fscanf(file, "%d %d", &rows, &cols);
  }
  initMazeSize(maze, rows, cols);

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

  initMaze(maze);

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
}

int main (int argc, char **argv)
{
  FILE *src = NULL;
  
  if (!validateInput(argc, argv, &src)) {
    printf("Goodbye!\n");
    return -1;
  }

  if (is_debug)
    printf("In debug mode!\n");

  Maze *m1 = createMaze();

  readInput(src, m1);
  printMaze(m1);
}
