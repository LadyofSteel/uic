#include "GridDisplay.h"

int main ( int argc, char** argv )
{
  int i;

  GridDisplay gd(20, 20);
  gd.showGrid ( );

  // show one change ever second
  for ( i = 0 ; i < 20 ; i++ )
  {
    gd.mySleep ( 1000 );

    char ch = (char) ( (int) 'a' + i );
    gd.setChar(i,i, ch);

    gd.showGrid ( );
  }

  // show multiple positions change "at once"
  for ( i = 7 ; i < 17 ; i++ )
  {
    gd.setChar ( 3, i, '$');
  }
  gd.showGrid ( );

  int j,k;
  // alternate between 2 "flashing" values
  for ( i = 0 ; i < 20 ; i++ )
  {
    gd.mySleep ( 250 );
    for (j = 0 ; j < 4 ; j++)
      for ( k = 0 ; k < 4 ; k++ )
        gd.setChar ( 12+j, 4+k, '9');  
    gd.showGrid ( );

    gd.mySleep ( 250 );
    for (j = 0 ; j < 4 ; j++)
      for ( k = 0 ; k < 4 ; k++ )
        gd.setChar ( 12+j, 4+k, '6');  
    gd.showGrid ( );
  }

  return 1;
}

