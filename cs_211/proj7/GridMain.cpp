#include "GridDisplay.h"

int floop ( int argc, char** argv )
{
  int i;

  GridDisplay myGrid(20, 20);
  myGrid.showGrid ( );

  // show one change every second
  for ( i = 0 ; i < 20 ; i++ )
  {
    myGrid.mySleep ( 1000 );

    char ch = (char) ( (int) 'a' + i );
    myGrid.setChar(i,i, ch);

    myGrid.showGrid ( );
  }

  // show multiple positions change "at once"
  for ( i = 7 ; i < 17 ; i++ )
  {
    myGrid.setChar ( 3, i, '$');
  }
  myGrid.showGrid ( );

  int j,k;
  // alternate between 2 "flashing" values
  for ( i = 0 ; i < 20 ; i++ )
  {
    myGrid.mySleep ( 250 );
    for (j = 0 ; j < 4 ; j++)
      for ( k = 0 ; k < 4 ; k++ )
        myGrid.setChar ( 12+j, 4+k, '9');  
    myGrid.showGrid ( );

    myGrid.mySleep ( 250 );
    for (j = 0 ; j < 4 ; j++)
      for ( k = 0 ; k < 4 ; k++ )
        myGrid.setChar ( 12+j, 4+k, '6');  
    myGrid.showGrid ( );
  }

  return 1;
}

