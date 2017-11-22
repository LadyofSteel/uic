/**
 *  @brief Creature class header
 *
 *  @author Ammar Subei
 */

#pragma once

#include <string>

#include "island.h"

class Creature
{
  public:
    /**
     *  @brief Enum for type of creature
     */
    enum class Type
    {
      ANT,      ///< Ant
      DOODLEBUG ///< DoodleBug
    }

    /**
     *  @brief Default constructor
     */
    virtual Creature(Island& island)
    {
    }

    /**
     *  @brief Destructor
     */
    ~Creature();

    /**
     *  @brief Getter for x position
     */
    int getXPos()                 const { return xPos; }

    /**
     *  @brief Getter for y position
     */
    int getYPos()                 const { return yPos; }

    /**
     *  @brief Getter for last spawn day
     */
    int getLastSpawn()            const { return lastSpawned; }

    /**
     *  @brief Getter for creature's environment
     */
    Island getIsland()            const { return island; }

    /**
     *  @brief Setter for x position
     */
    void setXPos(const int x)           { xPos = x; }

    /**
     *  @brief Setter for y position
     */
    void setYPos(const int y)           { yPos = y; }

    /**
     *  @brief Setter for last spawn day
     */
    void setLastSpawn(const int value)  { lastSpawned = value; }

    /**
     *  @brief Setter for x position
     */
    void setIsland(const int value)     { yPos = y; }

    /**
     *  @brief Moves the creature
     */
    virtual bool move();

    /**
     *  @brief Spawns a new creature
     */
    virtual Creature spawn();

  private:
    Island island;    ///< Creature's environment
    int xPos;         ///< Current x position
    int yPos;         ///< Current y position
    int lastSpawned;  ///< Last day creature spawned a new creature
};
