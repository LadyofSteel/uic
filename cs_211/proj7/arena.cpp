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

  creatures = new Creature**[getRows()];

  for (int i = 0; i < getRows(); i++) {
    creatures[i] = new Creature*[getColumns()];

    for (int j = 0; j < getColumns(); j++) {
      creatures[i][j] = NULL;
    }
  }
}

Creature::Type Arena::getCreatureType(const int x, const int y) const
{
  if ( creatures[x][y] != NULL) {
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
    return (creatures[x][y] == NULL);
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
  creatures[x][y] = creature;
  grid->setChar(x, y, getCreatureSymbol(type));
  return true;
}

bool Arena::moveCreature(const int x, const int y, const int newX, const int newY)
{
  if ( !isValid(x, y) )
    return false;

  if ( !isValid(newX, newY) )
    return false;

  creatures[newX][newY] = creatures[x][y];
  creatures[x][y] = NULL;

  grid->setChar(x, y, getCreatureSymbol( creatures[x][y]->getType() ));
  grid->setChar(newX, newY, getCreatureSymbol( creatures[newX][newY]->getType() ));
  return true;
}
