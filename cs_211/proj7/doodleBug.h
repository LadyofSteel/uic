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
    /**
     *  @brief Default constructor
     */
    DoodleBug(Arena* arena) : Creature(arena)
    {
      setType(Type::DOODLEBUG);
    }

    /**
     *  @brief Getter for last ate day
     *  @return int last ate day
     */
    int getLastAte()            const { return lastAte; }

    /**
     *  @brief Setter for last ate day
     *  @param int new last ate day
     */
    void setLastAte(const int value)  { lastAte = value; }

    /**
     *  @brief Gets the position for an adjacent ant to eat
     *
     *  If no ants exist around the given position, the new positions
     *  will be set to -1.
     *
     *  @param int current x position
     *  @param int current y position
     *  @param int new x position
     *  @param int new y position
     */
    void getAntPosition(const int x, const int y, int& newX, int& newY);

    /**
     *  @brief Moves the doodlebug
     *  @return bool move successful
     */
    virtual bool move();

    /**
     *  @brief Spawns a new doodlebug
     *  @return bool spawn successful
     */
    virtual bool spawn();

    /**
     *  @brief Lives for one day
     */
    virtual void live();

  private:
    int lastAte;  ///< Last day the doodlebug ate
};
