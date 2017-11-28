/**
 *  @brief Creature class definitions
 *
 *  @author Ammar Subei
 */

#include "arena.h"
#include "creature.h"

Creature::Creature(Arena *arena)
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
}

bool Creature::move()
{
  return false;
}

void Creature::spawn()
{
}

void Creature::live()
{
}
