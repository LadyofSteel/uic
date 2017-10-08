#include <string.h>

#include "maze.h"
#include "stack.h"

/* verify the proper number of command line arguments were given */
bool validateInput(int arg_count, char **args, FILE *file)
{
  if (arg_count < 2) {  // No input arguments
    fprintf(stderr, "Usage: %s <input file name>\n", args[0]);
    return false;
  } else if(arg_count == 2) {  // Only '-d' flag input
    if ( !strcmp(args[1], "-d") ) {
      fprintf(stderr, "Usage: %s <input file name>\n", args[0]);
      return false;
    }

    file = fopen(args[1], "r");
  } else if(arg_count == 3) {  // Only '-d' flag input
  } else {
      fprintf(stderr, "Too many arguments given. Aborting...");
      return false;
  }

  file = fopen(args[1], "r");

  /* Try to open the input file. */
  if (file == NULL) {
    fprintf (stderr, "ERROR: Can't open input file: %s", args[1] );
    return false;
  }

  return true;
}

int main (int argc, char **argv)
{
  FILE *src = NULL;
  
  if (validateInput(argc, argv, src)) {
    printf("Goodbye!\n");
    return (-1);
  }

  Maze *m1 = createMaze();
  initMazeSize(m1, 30, 30);

  int xpos = 0;
  int ypos = 0;

  int i,j;
  /* read in the size, starting and ending positions in the maze */
  fscanf (src, "%d %d", &m1->x_size, &m1->y_size);
  fscanf (src, "%d %d", &m1->x_start, &m1->y_start);
  fscanf (src, "%d %d", &m1->x_end, &m1->y_end);

  /* print them out to verify the input */
  printf ("size: %d, %d\n", m1->x_size, m1->y_size);
  printf ("start: %d, %d\n", m1->x_start, m1->y_start);
  printf ("end: %d, %d\n", m1->x_end, m1->y_end);

  /* initialize the maze to empty */
  for (i = 0; i < m1->x_size+2; i++)
    for (j = 0; j < m1->y_size+2; j++)
      m1->data[i][j] = '.';

  /* mark the borders of the maze with *'s */
  for (i=0; i < m1->x_size+2; i++)
  {
    m1->data[i][0] = '*';
    m1->data[i][m1->y_size+1] = '*';
  }
  for (i=0; i < m1->y_size+2; i++)
  {
    m1->data[0][i] = '*';
    m1->data[m1->x_size+1][i] = '*';
  }

  /* mark the starting and ending positions in the maze */
  m1->data[m1->x_start][m1->y_start] = 's';
  m1->data[m1->x_end][m1->y_end] = 'e';

  /* mark the blocked positions in the maze with *'s */
  while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
    m1->data[xpos][ypos] = '*';

  /* print out the initial maze */
  for (i = 0; i < m1->x_size+2; i++)
  {
    for (j = 0; j < m1->y_size+2; j++)
      printf ("%c", m1->data[i][j]);
    printf("\n");
  }
}

