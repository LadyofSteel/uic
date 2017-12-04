/**
 *  @brief Ant class definitions
 *
 *  @author Ammar Subei
 */

#include "arena.h"
#include "ant.h"

bool Ant::spawn()
{
  Arena *arena = getArena();
  int lastSpawn = getLastSpawn();
  int newX = 0;
  int newY = 0;

  if (lastSpawn < 3) {
    return false;
  }

  getAdjacentPosition(getXPos(), getYPos(), newX, newY);

  // No adjacent spots available
  if (newX == -1 && newY == -1) {
    return false;
  }

  // Spawn a new Ant and move it to the new position immediately
  Ant *newAnt = new Ant(arena);
  arena->moveCreature(newAnt->getXPos(), newAnt->getYPos(), newX, newY);

  // Don't let the child ant take its turn for today
  newAnt->setDaySpent(true);

  setLastSpawn(-1);
  return true;
}

void Ant::live()
{
  move();

  if (getLastSpawn() >= 3) {
    spawn();
  }

  setDaySpent(true);
  setLastSpawn( getLastSpawn() + 1 );
}
