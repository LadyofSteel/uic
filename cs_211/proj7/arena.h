/**
 *  @brief Arena class header
 *
 *  @author Ammar Subei
 */

#pragma once 

#include "GridDisplay.h"
#include "creature.h"

class Arena
{
  public:
    /**
     *  @brief Default constructor
     */
    Arena(GridDisplay *grid);

    /**
     *  @brief Getter for number of rows
     *
     *  @return int number of rows
     */
    int getRows()                 const { return rows; }

    /**
     *  @brief Getter for number of columns
     *
     *  @return int number of columns
     */
    int getColumns()              const { return columns; }

    /**
     *  @brief Getter for grid object
     *
     *  @return GridDisplay grid object
     */
    GridDisplay* getGrid()        const { return grid; }

    /**
     *  @brief Setter for number of rows
     *
     *  @param int new number of rows
     */
    void setRows(const int newValue)    { rows = newValue; }

    /**
     *  @brief Setter for number of columns
     *
     *  @param int new number of columns
     */
    void setColumns(const int newValue) { columns = newValue; }

    /**
     *  @brief Setter for grid object
     *
     *  @param GridDisplay* new grid
     */
    void setGrid(GridDisplay *newGrid)  { grid = newGrid; }

    /**
     *  @brief Returns symbol for a given creature type
     *
     *  @param Type creature type
     *  @return char symbol for given creature type
     */
    char getCreatureSymbol(const Creature::Type type) const;

    /**
     *  @brief Checks if position is valid
     *
     *  A position is valid if it's within the arena
     *  boundaries and is not occupied by a creature.
     *
     *  @param int x position
     *  @param int y position
     *  @return bool position is valid
     */
    bool isValid(const int x, const int y) const;

    /**
     *  @brief Adds new creature
     *
     *  @param Creature new creature
     *  @param int x position
     *  @param int y position
     *  @return bool add successful
     */
    bool addCreature(Creature *creature, const int x, const int y);

    /**
     *  @brief Moves creature in a random direction
     *
     *  @param int current x position
     *  @param int current y position
     *  @param int new x position
     *  @param int new y position
     *  @return bool move successful
     */
    bool moveCreature(const int x, const int y, const int newX, const int newY);

  private:
    Creature::Type **creatureLocations; ///< 2D array of creature types
    int rows;                           ///< Number of rows for arena
    int columns;                        ///< Number of columns for arena
    GridDisplay *grid;                  ///< Object to display the grid
};
