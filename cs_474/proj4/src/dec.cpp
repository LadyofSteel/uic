/**
 *  @brief Declare instruction class definition
 *
 *  @author Ammar Subei
*/

#include "ali.h"
#include "dec.h"

void DEC::execute(ALI &receiver)
{
  receiver.addSymbol(getArgument(), receiver.getPC());

  // Increment program counter
  receiver.setPC( receiver.getPC() + 1 );
}
