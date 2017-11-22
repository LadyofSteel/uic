/**
 *  @brief Ant class header
 *
 *  @author Ammar Subei
 */

#pragma once

#include <string>

#include "creature.h"

class Ant : public Creature
{
  public:
    Ant(Arena& arena) : Creature(arena)
    {
      setType(Type::ANT);
    }

  private:
};
