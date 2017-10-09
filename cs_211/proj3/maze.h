/**
 *  @brief CS 211 Project 3
 *
 *  Maze file header.
 *
 *  @author Ammar Subei
*/

#ifndef MAZE_H
#define MAZE_H

#include "stack.h"

#include <stdio.h>

/**
 *  @brief MazeData struct that holds the data for each position
*/
typedef struct MazeData
{
  char symbol;      //!< Character for maze display
  bool is_visited;  //!< Check if this spot was visited
} MazeData;

/**
 *  @brief Maze struct that has all info about a maze
*/
typedef struct Maze
{
  MazeData **data;      //!< 2-D array of maze data
  int rows, columns;    //!< Maze dimensions
  int x_start, y_start; //!< Coordinates for start position
  int x_end, y_end;     //!< Coordinates for end position
} Maze;

/**
 *  @brief Create a new Maze object
 *
 *  @return new Maze object
*/
Maze* createMaze();

/**
 *  @brief Cleans up given maze
 *
 *  @param Maze object to clean up
*/
void cleanupMaze(Maze *maze);

/**
 *  @brief Initializes the maze with given dimensions
 *
 *  @param int number of rows
 *  @param int number of columns
*/
void initMazeSize(Maze *maze, const int rows, const int columns);

/**
 *  @brief Initializes the internals of the maze
 *
 *  This function basically initializes every maze element.
 *  The maze will have its borders, along with the starting and
 *  ending positions all marked.
*/
void initMaze(Maze *maze);

/**
 *  @brief Checks if the position in the maze is blocked
 *
 *  @param Maze object
 *  @param int row number
 *  @param int column number
 *  @return position is blocked
*/
bool isBlocked(const Maze *maze, const int row, const int col);

/**
 *  @brief Checks if the position in the maze was visited before
 *
 *  @param Maze object
 *  @param int row number
 *  @param int column number
 *  @return position was visited
*/
bool isVisited(const Maze *maze, const int row, const int col);

/**
 *  @brief Marks the given position in the maze as visited
 *
 *  @param Maze object
 *  @param int row number
 *  @param int column number
*/
void markVisited(Maze *maze, const int row, const int col);

/**
 *  @brief Prints out a visual of the maze
 *
 *  @param Maze object
*/
void printMaze(const Maze *maze);

#endif /* MAZE_H */
