#include "maze.h"

Maze* createMaze()
{
  Maze *newMaze = (Maze *) malloc( sizeof(Maze) );
  return newMaze;
}

void initMazeSize(Maze *maze, const int rows, const int columns)
{
  maze->x_size = columns;
  maze->y_size = rows;

  maze->data = (char **) malloc( sizeof(char*) * rows );

  int i;
  for (i = 0; i < rows; i++)
    maze->data[i]= (char *) malloc( sizeof(char) * columns );
}

void printMaze(const Maze *maze)
{
}
