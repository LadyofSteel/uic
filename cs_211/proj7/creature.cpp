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
  } while ( !arena->isValid(x, y) );

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

  if (!arena->isValid(x, y - 1) &&
      !arena->isValid(x, y + 1) &&
      !arena->isValid(x - 1, y) &&
      !arena->isValid(x + 1, y) ) {
    newX = -1;
    newY = -1;
    return;
  }

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
  } while ( !arena->isValid(newX, newY) );
}

bool Creature::move()
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
