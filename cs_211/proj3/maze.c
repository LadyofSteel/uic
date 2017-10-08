#include <stdlib.h>

#include "maze.h"

Maze* createMaze()
{
  Maze *newMaze = (Maze *) malloc( sizeof(Maze) );
  newMaze->rows = 0;
  newMaze->columns = 0;
  newMaze->x_start = 0;
  newMaze->y_start = 0;
  newMaze->x_end = 0;
  newMaze->y_end = 0;

  return newMaze;
}

void initMazeSize(Maze *maze, const int rows, const int columns)
{
  maze->rows = rows;
  maze->columns = columns;

  maze->data = (MazeData **) malloc( (sizeof(MazeData*) * rows) + 2);

  int i;
  for (i = 0; i < rows + 2; i++)
    maze->data[i]= (MazeData *) malloc( (sizeof(MazeData) * columns) + 2);
}

void initMaze(Maze *maze)
{
  int i;
  int j;

  // Initialize the maze to empty with "."s
  for (i = 0; i < maze->rows + 2; i++) {
    for (j = 0; j < maze->columns + 2; j++) {
      maze->data[i][j].symbol = '.';
    }
  }

  // Mark the borders with "*"s
  for (i = 0; i < maze->rows + 2; i++) {
    maze->data[i][0].symbol = '*';
    maze->data[i][maze->columns + 1].symbol = '*';
  }
  for (i = 0; i < maze->columns + 2; i++) {
    maze->data[0][i].symbol = '*';
    maze->data[maze->rows + 1][i].symbol = '*';
  }

  // Mark start and end positions
  maze->data[maze->x_start][maze->y_start].symbol = 's';
  maze->data[maze->x_end][maze->y_end].symbol = 'e';
}

void printMaze(const Maze *maze)
{
  // Print maze info
  printf ("size: %d, %d\n", maze->rows, maze->columns);
  printf ("start: %d, %d\n", maze->x_start, maze->y_start);
  printf ("end: %d, %d\n", maze->x_end, maze->y_end);

  // Print out visual maze
  int i, j;
  for (i = 0; i < maze->rows + 2; i++)
  {
    for (j = 0; j < maze->columns + 2; j++)
      printf ("%c", maze->data[i][j].symbol);
    printf("\n");
  }
}
