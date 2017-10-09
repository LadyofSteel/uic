#include <stdlib.h>

#include "maze.h"

Maze* createMaze()
{
  Maze *new_maze = (Maze *) malloc( sizeof(Maze) );
  new_maze->rows = 0;
  new_maze->columns = 0;
  new_maze->x_start = 0;
  new_maze->y_start = 0;
  new_maze->x_end = 0;
  new_maze->y_end = 0;

  return new_maze;
}
void cleanupMaze(Maze *maze)
{
  /*int i;*/
  /*for (i = 0; i < maze->rows + 2; i++) {*/
    /*free(maze->data[i]);*/
  /*}*/

  /*free(maze->data);*/
  free(maze);
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

bool isBlocked(const Maze *maze, const int row, const int col)
{
  return maze->data[row][col].symbol == '*';
}

bool isVisited(const Maze *maze, const int row, const int col)
{
  return maze->data[row][col].is_visited;
}

void markVisited(Maze *maze, const int row, const int col)
{
  maze->data[row][col].is_visited = true;
}

void printMaze(const Maze *maze)
{
  // Print maze info
  printf("\n");
  printf("size: %d, %d\n", maze->rows, maze->columns);
  printf("start: %d, %d\n", maze->x_start, maze->y_start);
  printf("end: %d, %d\n", maze->x_end, maze->y_end);

  // Print out visual maze
  int i, j;
  for (i = 0; i < maze->rows + 2; i++) {
    for (j = 0; j < maze->columns + 2; j++)
      printf("%c", maze->data[i][j].symbol);
    printf("\n");
  }
}
