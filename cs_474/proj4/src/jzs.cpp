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
    receiver.setPC( receiver.getPC() + 1 );
  }
}
