/**
 *  @brief Ant class header
 *
 *  @author Ammar Subei
 */

#pragma once

#include "creature.h"

class Ant : public Creature
{
  public:
    /**
     *  @brief Default constructor
     */
    Ant(Arena* arena) : Creature(arena, Type::ANT)
    {
    }

    /**
     *  @brief Spawns a new ant
     *
     *  @return bool spawn successful
     */
    virtual bool spawn();

    /**
     *  @brief Lives for one day
     */
    virtual void live();
};
