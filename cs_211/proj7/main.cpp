
#include <cstdlib>
#include <ctime>

#include "GridDisplay.h"
#include "creature.h"
#include "doodleBug.h"
#include "ant.h"
#include "arena.h"

int main(int argc, char** argv)
{
  srand( time(NULL) );

  // Uncomment these variables to have limited existence
  // time for all creatures
  //int day = 0;
  //int existence = 20;

  int antCount = 50;
  int doodleCount = 10;

  GridDisplay *myGrid = new GridDisplay(20, 20);
  Arena *myArena = new Arena(myGrid);

  Ant **ants = new Ant*[antCount];
  DoodleBug **doodlebugs = new DoodleBug*[doodleCount];

  for (int i = 0; i < antCount; i++) {
    ants[i] = new Ant(myArena);
  }

  for (int i = 0; i < doodleCount; i++) {
    doodlebugs[i] = new DoodleBug(myArena);
  }

  myGrid->showGrid();

  // Use this while condition to limited program execution,
  // and uncomment the increment of day
  //while (day < existence) {

  while (true) {
    //day++;

    // DoodleBugs turn
    myArena->runDay(Creature::Type::DOODLEBUG);

    // Ants turn
    myArena->runDay(Creature::Type::ANT);

    // End of day cleanup
    myArena->endDay();

    myGrid->mySleep(800);
    myGrid->showGrid();
  }
}
