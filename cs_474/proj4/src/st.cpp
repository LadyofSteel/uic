/**
 *  @brief Store instruction class definition
 *
 *  @author Ammar Subei
*/

#include "ali.h"
#include "st.h"

void ST::execute(ALI &receiver)
{
  const std::string data = std::to_string(receiver.getRegA());
  const int address = receiver.getSymbolAddress( getArgument() );
  
  // Must change instruction at address to be able to hold the data in RegA.
  // We do that by making the type NONE and setting argument to data from RegA.
  ( receiver.getMemData(address) )->setType(Instruction::Type::NONE);
  ( receiver.getMemData(address) )->setArgument(data);

  // Increment program counter
  receiver.setPC( receiver.getPC() + 1 );
}
