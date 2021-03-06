/**
 *  @brief Creature class header
 *
 *  @author Ammar Subei
 */

#pragma once

// Declaration of class Arena to avoid circular dependency
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
     *
     *  @param Arena pointer to creature's arena
     *  @param Type of creature
     */
    Creature(Arena *arena, Type t);

    /**
     *  @brief Destructor
     */
    virtual ~Creature() {}

    /**
     *  @brief Getter for type of creature
     *
     *  @return Type type of creature
     */
    Creature::Type getType()        const { return type; }

    /**
     *  @brief Checks if current day was spent
     *
     *  @return bool day was spent
     */
    bool isDaySpent()               const { return daySpent; }

    /**
     *  @brief Getter for x position
     *
     *  @return int current x position
     */
    int getXPos()                   const { return xPos; }

    /**
     *  @brief Getter for y position
     *
     *  @return int current y position
     */
    int getYPos()                   const { return yPos; }

    /**
     *  @brief Getter for last spawn day
     *
     *  @return int last spawn day
     */
    int getLastSpawn()              const { return lastSpawned; }

    /**
     *  @brief Getter for creature's arena
     *
     *  @return Arena* creature's arena
     */
    Arena* getArena()               const { return arena; }

    /**
     *  @brief Setter for type of creature
     *
     *  @param Type new creature type
     */
    void setType(const Creature::Type t)  { type = t; }

    /**
     *  @brief Setter for day spent
     *
     *  @param bool day was spent
     */
    void setDaySpent(const bool value)    { daySpent = value; }

    /**
     *  @brief Setter for x position
     *
     *  @param int new x position
     */
    void setXPos(const int x)             { xPos = x; }

    /**
     *  @brief Setter for y position
     *
     *  @param int new y position
     */
    void setYPos(const int y)             { yPos = y; }

    /**
     *  @brief Setter for last spawn day
     *
     *  @param int new last spawn day
     */
    void setLastSpawn(const int value)    { lastSpawned = value; }

    /**
     *  @brief Setter for creature's arena
     *
     *  @param Arena* new creature arena
     */
    void setArena(Arena *newArena)        { arena = newArena; }

    /**
     *  @brief Getter for a valid adjacent position
     *
     *  It first checks if at least one adjacent position is valid.
     *  If all adjacent positions are invalid, then the new positions
     *  will be set to -1.
     *
     *  @param int current x position
     *  @param int current y position
     *  @param int output new x position
     *  @param int output new y position
     */
    void getAdjacentPosition(const int x, const int y, int& newX, int& newY);

    /**
     *  @brief Moves the creature
     *
     *  @return bool move successful
     */
    bool move();

    /**
     *  @brief Spawns a new creature
     *
     *  @return bool spawn successful
     */
    virtual bool spawn() = 0;

    /**
     *  @brief Lives for one day
     */
    virtual void live() = 0;

  protected:
    Type type;        ///< Creature's type
    Arena *arena;     ///< Creature's environment
    bool daySpent;    ///< Creature spent its day
    int xPos;         ///< Current x position
    int yPos;         ///< Current y position
    int lastSpawned;  ///< Last day creature spawned a new creature
};
