/**
 *  @brief Arena class definitions
 *
 *  @author Ammar Subei
 */

#include "arena.h"

Arena::Arena(GridDisplay *grid)
{
  setGrid(grid);
  setRows(20);
  setColumns(20);

  creatureLocations = new Creature::Type*[getRows()];

  for (int i = 0; i < getRows(); i++) {
    creatureLocations[i] = new Creature::Type[getColumns()];

    for (int j = 0; j < getColumns(); j++) {
      creatureLocations[i][j] = Creature::Type::NONE;
    }
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
    return (creatureLocations[x][y] == Creature::Type::NONE);
  } else {
    return false;
  }
}

bool Arena::addCreature(Creature *creature)
{
  int x = creature->getXPos();
  int y = creature->getYPos();

  if ( !isValid(x, y) )
    return false;

  Creature::Type type = creature->getType();
  creatureLocations[x][y] = type;
  grid->setChar(x, y, getCreatureSymbol(type));
  return true;
}

bool Arena::moveCreature(const int x, const int y, const int newX, const int newY)
{
  if ( !isValid(x, y) )
    return false;

  if ( !isValid(newX, newY) )
    return false;

  creatureLocations[newX][newY] = creatureLocations[x][y];
  creatureLocations[x][y] = Creature::Type::NONE;

  grid->setChar(x, y, getCreatureSymbol(creatureLocations[x][y]));
  grid->setChar(newX, newY, getCreatureSymbol(creatureLocations[newX][newY]));
  return true;
}
