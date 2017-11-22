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
     *  @return int number of rows
     */
    int getRows()                 const { return rows; }

    /**
     *  @brief Getter for number of columns
     *  @return int number of columns
     */
    int getColumns()              const { return columns; }

    /**
     *  @brief Getter for grid object
     *  @return GridDisplay grid object
     */
    GridDisplay* getGrid()        const { return grid; }

    /**
     *  @brief Setter for number of rows
     *  @param int new number of rows
     */
    void setRows(const int newValue)    { rows = newValue; }

    /**
     *  @brief Setter for number of columns
     *  @param int new number of columns
     */
    void setColumns(const int newValue) { columns = newValue; }

    /**
     *  @brief Setter for grid object
     *  @param GridDisplay* new grid
     */
    void setGrid(GridDisplay *newGrid)  { grid = newGrid; }

    /**
     *  @brief Checks if position is valid
     *  @param int position to check
     *  @return bool position is valid
     */
    bool isValid(const int value) const;

  private:
    Creature::Type **creatureLocations; ///< 2D array of creature types
    int rows;                           ///< Number of rows for arena
    int columns;                        ///< Number of columns for arena
    GridDisplay *grid;                  ///< Object to display the grid
};
