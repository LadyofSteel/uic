#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Maze
{
  char **data;          //!< 2-D character array of the maze
  int x_size, y_size;   //!< Dimensions of the maze
  int x_start, y_start; //!< Coordinates for start position
  int x_end, y_end;     //!< Coordinates for end position
} Maze;

Maze* createMaze();
void initMazeSize(Maze *maze, const int rows, const int columns);
void printMaze(const Maze *maze);

#endif /* MAZE_H */
