/**
 *  @brief Main file
 *
 *  @author Ammar Subei
 */

#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "doodleBug.h"
#include "ant.h"
#include "arena.h"

int getDelay(const int argc, char** argv)
{
  if (argc == 3) {
    if ( !strcmp(argv[1], "-d") ) {
      try {
        return std::stoi(argv[2]);
      } catch (std::invalid_argument&) {
      }
    }
  }

  return 600;
}

void run(Arena *arena, GridDisplay *grid, const int delay)
{
  while (true) {
    // DoodleBugs turn
    arena->runDay(Creature::Type::DOODLEBUG);

    // Ants turn
    arena->runDay(Creature::Type::ANT);

    // End of day cleanup
    arena->endDay();

    // Display grid
    grid->mySleep(delay);
    grid->showGrid();
  }
}

int main(int argc, char** argv)
{
  srand( time(NULL) );

  int delay = getDelay(argc, argv);
  int antCount = 100;
  int doodleCount = 5;

  GridDisplay *myGrid = new GridDisplay(20, 20);
  Arena *myArena = new Arena(myGrid);

  Ant **ants = new Ant*[antCount];
  DoodleBug **doodlebugs = new DoodleBug*[doodleCount];

  // Spawn initial Ants
  for (int i = 0; i < antCount; i++) {
    ants[i] = new Ant(myArena);
  }

  // Spawn initial DoodleBugs
  for (int i = 0; i < doodleCount; i++) {
    doodlebugs[i] = new DoodleBug(myArena);
  }

  // Display initial grid
  myGrid->showGrid();

  // Run the simulation
  run(myArena, myGrid, delay);

  // Done
  return 0;
}
