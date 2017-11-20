/**
 *  @brief Airport definitions
 *
 *  @author Ammar Subei
 */

#include "airport.h"

Airport::Airport()
{
  setNumber(-1);
  setVisited(false);
}

Airport::Airport(int number, bool visited)
{
  setNumber(number);
  setVisited(visited);
}

bool Airport::operator==(const Airport& rhs)
{
  return getNumber() == rhs.getNumber();
}
