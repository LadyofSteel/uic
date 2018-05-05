/**
 *  @brief Jump zero instruction class definition
 *
 *  @author Ammar Subei
*/

#include "ali.h"
#include "jzs.h"

void JZS::execute(ALI &receiver)
{
  if (receiver.isZero()) {
    receiver.setPC( std::stoi(getArgument()) );
  } else {
    // Increment program counter
    receiver.setPC( receiver.getPC() + 1 );
  }
}
