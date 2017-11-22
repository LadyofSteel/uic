#include <cstdlib>
#include <ctime>

#include "GridDisplay.h"

class Beetle;

class Island
{
  private:
    Beetle* **location;  // Dynamic 2D array of pointers
    int rows;
    int cols;
    GridDisplay *gd;

  public:
    Island(GridDisplay *grid)
    {
      gd = grid;
      rows = 20;
      cols = 20;
      location = new Beetle**[rows];

      for ( int i = 0 ; i < rows ; i++ )
      {
        location[i] = new Beetle*[cols];
        for ( int j = 0 ; j < cols ; j++ )
        {
          location[i][j] = NULL;
        }
      }
    }

    int getRows()
    {
      return rows;
    }

    int getCols()
    {
      return cols;
    }

    bool isValid (int r, int c)
    {
      if (( r >= 0 && r < rows ) && ( c >= 0 && c < cols))
        return true;
      else
        return false;
    }

    bool isOccupied (int r, int c)
    {
      if ( location[r][c] == NULL )
        return false;
      else
        return true;
    }

    bool addBeetle (Beetle* b, int r, int c)
    {
      // verify to location is valid
      if ( isValid (r, c) == false )
        return false;
      // verify to location is empty
      if ( isOccupied (r, c) == true)
        return false;

      location[r][c] = b;
      gd->setChar (r,c,'@');
      return true;
    }

    bool moveBeetle (int currX, int currY, int nextX, int nextY)
    {
      // verify to/from locations are valid
      if ( isValid (currX, currY) == false )
        return false;
      if ( isValid (nextX, nextY) == false )
        return false;
      // verify a beetle exists at current location
      if ( isOccupied (currX, currY) == false)
        return false;
      // verify to location is empty
      if ( isOccupied (nextX, nextY) == true)
        return false;

      location[nextX][nextY] = location[currX][currY]; 
      location[currX][currY] = NULL; 
      gd->setChar (currX, currY, '.');
      gd->setChar (nextX, nextY, '@');
      return true;
    }
};


class Beetle
{
  private:
    Island* isl;
    int row;
    int col;
    int dayLastMoved;

  public:
    Beetle(Island *island)
    {
      isl = island;

      do  // randomly select a location until an empty location is found
      {
        row = rand() % island->getRows();   
        col = rand() % island->getCols();   
      }
      while ( island->addBeetle (this, row, col) == false );

      dayLastMoved = 0;
    }

    void move()
    {
      wander();
      //spawn();
    }

    void wander ()
    {
      int nextX = -999;
      int nextY = -999;
      int direction = rand() % 4;
      if ( direction == 0 ) // attempt to move left
      {
        nextX = row;
        nextY = col-1;
      }
      else if ( direction == 1 ) // attempt to move right
      {
        nextX = row;
        nextY = col+1;
      }
      else if ( direction == 2 ) // attempt to move up
      {
        nextX = row-1;
        nextY = col;
      }
      else if ( direction == 3 ) // attempt to move down
      {
        nextX = row+1;
        nextY = col;
      }

      if ( isl->moveBeetle ( row, col, nextX, nextY ) == true )
      {
        row = nextX;
        col = nextY;
      }
    }
};

int main ( int argc, char** argv)
{
  srand(time(NULL));

  GridDisplay gd;
  Island island(&gd);
  int day = 0;

  int bugCount = 1;
  Beetle** bugs;  // create an dynamic array of beetle pointers
  bugs = new Beetle*[bugCount];
  for (int i = 0 ; i < bugCount ; i++)
    bugs[i] = new Beetle (&island);

  // show the initial locations of the beetles
  gd.showGrid();

  // loop for 20 days
  while ( day < 20 )
  {
    day++;

    // move each beetle in the "bug array"
    for (int i = 0 ; i < bugCount ; i++)
    {
      bugs[i]->move();
    }

    // pause execution to allow "animation" to be seen
    gd.mySleep( 1000 );
    gd.showGrid();
  }

}
