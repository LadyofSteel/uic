/**
 *  @brief DoodleBug class definitions
 *
 *  @author Ammar Subei
 */

#include "arena.h"
#include "doodleBug.h"

void DoodleBug::getAntPosition(const int x, const int y, int& newX, int& newY)
{
  Arena *arena = getArena();

  // Check if at least one spot is valid
  if (!arena->isValid(x, y - 1) ||
      !arena->isValid(x, y + 1) ||
      !arena->isValid(x - 1, y) ||
      !arena->isValid(x + 1, y) ) {
    newX = -1;
    newY = -1;
    return;
  }

  // Check if at least one spot has an ant
  if (arena->getCreatureType(x, y - 1) != Type::ANT &&
      arena->getCreatureType(x, y + 1) != Type::ANT &&
      arena->getCreatureType(x - 1, y) != Type::ANT &&
      arena->getCreatureType(x + 1, y) != Type::ANT) {
    newX = -1;
    newY = -1;
    return;
  }

  // At least one adjacent spot has an ant,
  // so we choose a spot randomly to avoid patterns
  do {
    int direction = rand() % 4;

    switch (direction) {
      case 0:
        newX = x;
        newY = y - 1;
        break;
      case 1:
        newX = x;
        newY = y + 1;
        break;
      case 2:
        newX = x - 1;
        newY = y;
        break;
      case 3:
        newX = x + 1;
        newY = y;
        break;
      default:
        break;
    }
  } while ( arena->getCreatureType(newX, newY) != Type::ANT );
}

bool DoodleBug::hunt()
{
  int newX = 0;
  int newY = 0;

  getAntPosition(getXPos(), getYPos(), newX, newY);

  // No ants available
  if (newX == -1 && newY == -1) {
    return false;
  }

  if ( !getArena()->killCreature(newX, newY) ) {
    return false;
  }

  if ( !getArena()->moveCreature(getXPos(), getYPos(), newX, newY) ) {
    return false;
  }

  setXPos(newX);
  setYPos(newY);
  setLastAte(-1);

  return true;
}

bool DoodleBug::spawn()
{
  Arena *arena = getArena();
  int lastSpawn = getLastSpawn();
  int newX = 0;
  int newY = 0;

  if (lastSpawn < 8) {
    return false;
  }

  getAdjacentPosition(getXPos(), getYPos(), newX, newY);

  // No adjacent spots available
  if (newX == -1 && newY == -1) {
    return false;
  }

  DoodleBug *newBug = new DoodleBug(arena);
  arena->moveCreature(newBug->getXPos(), newBug->getYPos(), newX, newY);

  newBug->setLastAte(0);

  // Don't let the doodlebug take its turn for today
  newBug->setDaySpent(true);

  setLastSpawn(-1);
  return true;
}

void DoodleBug::live()
{
  if ( !hunt() ) {
    move();
  }

  if (getLastSpawn() >= 8) {
    spawn();
  }

  if (getLastAte() >= 3) {
    getArena()->killCreature( getXPos(), getYPos() );
    return;
  }

  setDaySpent(true);
  setLastAte( getLastAte() + 1 );
  setLastSpawn( getLastSpawn() + 1 );
}
