/**
 *  @brief Airport header file
 *
 *  @author Ammar Subei
 */
#pragma once

#include "myList.h"

class Airport
{
  private:
    bool visited;
    int airportNumber;
    MyList<int> adjacencyList;

  public:
    /**
     *  @brief Default constructor
     */
    Airport();

    /**
     *  @brief Secondary constructor
     */
    Airport(int number, bool visited);

    /**
     *  @brief Getter for airport number
     *  @return int airport number
    */
    int getNumber()             const { return airportNumber; }

    /**
     *  @brief Getter for adjacency list
     *  @return MyList adjacency list
    */
    MyList<int> getList()       const { return adjacencyList; }

    /**
     *  @brief Getter for visited status
     *  @return bool visited status
    */
    bool isVisited()            const { return visited; }

    /**
     *  @brief Setter for airport number
     *  @param int new number
    */
    void setNumber(const int value)   { airportNumber = value; }

    /**
     *  @brief Setter for visited status
     *  @param bool new visited status
    */
    void setVisited(const bool value) { visited = value; }

    /**
     *  @brief Overloads == operator to compare airports
     *  @param Airport rhs to compare to
     *  @return bool lhs airport number equals that of rhs
    */
    bool operator==(const Airport& rhs);
};
