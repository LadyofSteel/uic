/**
 *  @brief Creature class header
 *
 *  @author Ammar Subei
 */

#pragma once

#include <string>
#include <cstdlib>

class Arena;

class Creature
{
  public:
    /**
     *  @brief Enum for type of creature
     */
    enum class Type
    {
      NONE,     ///< Not a creature
      ANT,      ///< Ant
      DOODLEBUG ///< DoodleBug
    };

    /**
     *  @brief Default constructor
     */
    Creature(Arena *arena);

    /**
     *  @brief Destructor
     */
    ~Creature();

    /**
     *  @brief Getter for type of creature
     *  @return Type type of creature
     */
    Creature::Type getType()        const { return type; }

    /**
     *  @brief Getter for x position
     *  @return int current x position
     */
    int getXPos()                   const { return xPos; }

    /**
     *  @brief Getter for y position
     *  @return int current y position
     */
    int getYPos()                   const { return yPos; }

    /**
     *  @brief Getter for last spawn day
     *  @return int last spawn day
     */
    int getLastSpawn()              const { return lastSpawned; }

    /**
     *  @brief Getter for creature's arena
     *  @return Arena* creature's arena
     */
    Arena* getArena()               const { return arena; }

    /**
     *  @brief Setter for type of creature
     *  @param Type new creature type
     */
    void setType(const Creature::Type t)  { type = t; }

    /**
     *  @brief Setter for x position
     *  @param int new x position
     */
    void setXPos(const int x)             { xPos = x; }

    /**
     *  @brief Setter for y position
     *  @param int new y position
     */
    void setYPos(const int y)             { yPos = y; }

    /**
     *  @brief Setter for last spawn day
     *  @param int new last spawn day
     */
    void setLastSpawn(const int value)    { lastSpawned = value; }

    /**
     *  @brief Setter for creature's arena
     *  @param Arena* new creature arena
     */
    void setArena(Arena *newArena)        { arena = newArena; }

    /**
     *  @brief Moves the creature
     *  @return bool move successful
     */
    bool move();

    /**
     *  @brief Spawns a new creature
     */
    void spawn();

    /**
     *  @brief Lives for one day
     */
    virtual void live();

  protected:
    Type type;        ///< Creature's type
    Arena *arena;     ///< Creature's environment
    int xPos;         ///< Current x position
    int yPos;         ///< Current y position
    int lastSpawned;  ///< Last day creature spawned a new creature
};
