/**
 *  @brief Jump overflow instruction class definition
 *
 *  @author Ammar Subei
*/

#include "ali.h"
#include "jvs.h"

void JVS::execute(ALI &receiver)
{
  if (receiver.isOverflow()) {
    receiver.setPC( std::stoi(getArgument()) );
  }
}
