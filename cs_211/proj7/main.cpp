
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

  int day = 0;
  int antCount = 0;
  int doodleCount = 5;

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

  while (day < 10) {
    day++;

    // DoodleBugs turn
    myArena->runDay(Creature::Type::DOODLEBUG);

    // Ants turn
    myArena->runDay(Creature::Type::ANT);

    // End of day cleanup
    myArena->endDay();

    myGrid->mySleep(1000);
    myGrid->showGrid();
  }
}
