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

bool DoodleBug::move()
{
  int newX = 0;
  int newY = 0;

  getAdjacentPosition(getXPos(), getYPos(), newX, newY);

  if (newX == -1 && newY == -1) {
    return false;
  }

  if ( !getArena()->moveCreature(getXPos(), getYPos(), newX, newY) ) {
    return false;
  }

  setXPos(newX);
  setYPos(newY);

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

  if (newX == -1 && newY == -1) {
    return false;
  }

  DoodleBug *newBug = new DoodleBug(arena);
  arena->moveCreature(newBug->getXPos(), newBug->getYPos(), newX, newY);

  newBug->setXPos(newX);
  newBug->setYPos(newY);
  newBug->setLastAte(0);

  setLastSpawn(0);
  return true;
}

void DoodleBug::live()
{
}
