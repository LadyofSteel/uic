/**
 *  @brief Creature class definitions
 *
 *  @author Ammar Subei
 */

#include <iostream>

#include "arena.h"
#include "creature.h"

Creature::Creature(Arena *arena, Type t)
{
  setArena(arena);

  int x = 0;
  int y = 0;

  do {
    x = rand() % arena->getRows();
    y = rand() % arena->getColumns();
  } while ( !(arena->isValid(x, y) && !arena->isOccupied(x, y)) );

  setXPos(x);
  setYPos(y);
  setType(t);
  setDaySpent(false);
  setLastSpawn(0);

  arena->addCreature(this);
}

void Creature::getAdjacentPosition(const int x, const int y, int& newX, int& newY)
{
  Arena *arena = getArena();

  int unavailableSpots = 0;

  // Must check if any adjacent spot is both valid and not occupied
  if ( arena->isValid(x, y - 1) ) {
    if ( arena->isOccupied(x, y - 1) ) {
      unavailableSpots++;
    }
  } else {
    unavailableSpots++;
  }

  if ( arena->isValid(x, y + 1) ) {
    if ( arena->isOccupied(x, y + 1) ) {
      unavailableSpots++;
    }
  } else {
    unavailableSpots++;
  }

  if ( arena->isValid(x - 1, y) ) {
    if ( arena->isOccupied(x - 1, y) ) {
      unavailableSpots++;
    }
  } else {
    unavailableSpots++;
  }

  if ( arena->isValid(x + 1, y) ) {
    if ( arena->isOccupied(x + 1, y) ) {
      unavailableSpots++;
    }
  } else {
    unavailableSpots++;
  }

  // No adjacent spots are both valid and unoccupied
  if (unavailableSpots >= 4) {
    newX = -1;
    newY = -1;
    return;
  }

  // At least one adjacent spot is available,
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
  } while ( !(arena->isValid(newX, newY) && !arena->isOccupied(newX, newY)) );
}

bool Creature::move()
{
  int newX = 0;
  int newY = 0;

  getAdjacentPosition(getXPos(), getYPos(), newX, newY);

  // No adjacent spots available
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
