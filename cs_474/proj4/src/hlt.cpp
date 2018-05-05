/**
 *  @brief Halt instruction class definition
 *
 *  @author Ammar Subei
*/

#include "hlt.h"

void HLT::execute(ALI &receiver)
{
  receiver.setHalt(true);
}
