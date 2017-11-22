/**
 *  @brief DoodleBug class header
 *
 *  @author Ammar Subei
 */

#pragma once

#include <string>

#include "creature.h"

class DoodleBug : public Creature
{
  public:
    DoodleBug(Arena& arena) : Creature(arena)
    {
      setType(Type::DOODLEBUG);
    }

  private:
};
