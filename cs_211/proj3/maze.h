#ifndef MAZE_H
#define MAZE_H

#include "stack.h"

#include <stdio.h>

typedef struct MazeData
{
  char symbol;      //!< Character for maze display
  bool is_visited;  //!< Check if this spot was visited
} MazeData;

typedef struct Maze
{
  MazeData **data;      //!< 2-D array of maze data
  int rows, columns;    //!< Maze dimensions
  int x_start, y_start; //!< Coordinates for start position
  int x_end, y_end;     //!< Coordinates for end position
} Maze;

Maze* createMaze();
void initMazeSize(Maze *maze, const int rows, const int columns);
void initMaze(Maze *maze);
void printMaze(const Maze *maze);

#endif /* MAZE_H */
