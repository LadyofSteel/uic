
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

bool Arena::isValid(const int value) const
{
  return false;
}
