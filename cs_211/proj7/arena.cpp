/**
 *  @brief Arena class definitions
 *
 *  @author Ammar Subei
 */

#include <iostream>

#include "arena.h"

Arena::Arena(GridDisplay *grid)
{
  setGrid(grid);
  setRows(20);
  setColumns(20);

  creatures = new Creature**[getRows()];

  for (int x = 0; x < getRows(); x++) {
    creatures[x] = new Creature*[getColumns()];

    for (int y = 0; y < getColumns(); y++) {
      creatures[x][y] = nullptr;
    }
  }
}

Creature::Type Arena::getCreatureType(const int x, const int y) const
{
  if (creatures[x][y]) {
    return creatures[x][y]->getType();
  } else {
    return Creature::Type::NONE;
  }
}

char Arena::getCreatureSymbol(const Creature::Type type) const
{
  switch (type) {
    case Creature::Type::NONE:
      return '.';
    case Creature::Type::ANT:
      return '*';
    case Creature::Type::DOODLEBUG:
      return '@';
    default:
      return '.';
  }
}

bool Arena::isValid(const int x, const int y) const
{
  if ((x >= 0 && x < getRows()) && (y >= 0 && y < getColumns())) {
    return true;
  } else {
    return false;
  }
}

bool Arena::isOccupied(const int x, const int y) const
{
  return (creatures[x][y] != nullptr);
}

bool Arena::addCreature(Creature *creature)
{
  int x = creature->getXPos();
  int y = creature->getYPos();

  if ( !isValid(x, y) )
    return false;

  if ( isOccupied(x, y) )
    return false;

  Creature::Type type = creature->getType();
  creatures[x][y] = creature;
  grid->setChar(x, y, getCreatureSymbol(type));

  return true;
}

bool Arena::moveCreature(const int x, const int y, const int newX, const int newY)
{
  if ( !isValid(newX, newY) )
    return false;

  if ( isOccupied(newX, newY) )
    return false;

  Creature::Type currentType = creatures[x][y]->getType();
  creatures[newX][newY] = creatures[x][y];
  creatures[x][y] = nullptr;

  grid->setChar(x, y, getCreatureSymbol(Creature::Type::NONE));
  grid->setChar(newX, newY, getCreatureSymbol(currentType));
  return true;
}

bool Arena::killCreature(const int x, const int y)
{
  if (creatures[x][y] == nullptr) {
    return false;
  }

  delete creatures[x][y];
  creatures[x][y] = nullptr;

  grid->setChar(x, y, getCreatureSymbol(Creature::Type::NONE));
  return true;
}

void Arena::runDay(const Creature::Type type)
{
  for (int x = 0; x < getRows(); x++) {
    for (int y = 0; y < getColumns(); y++) {
      Creature *creature = creatures[x][y];

      if (creature) {
        if ( creature->getType() == type && !creature->isDaySpent() ) {
          creature->live();
        }
      }
    }
  }
}

void Arena::endDay()
{
  for (int x = 0; x < getRows(); x++) {
    for (int y = 0; y < getColumns(); y++) {
      Creature *creature = creatures[x][y];

      if (creature) {
        creature->setDaySpent(false);
      }
    }
  }
}
