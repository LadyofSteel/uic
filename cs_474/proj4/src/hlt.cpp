/**
 *  @brief Halt instruction class definition
 *
 *  @author Ammar Subei
*/

#include "ali.h"
#include "hlt.h"

void HLT::execute(ALI &receiver)
{
  receiver.setHalt(true);
}
