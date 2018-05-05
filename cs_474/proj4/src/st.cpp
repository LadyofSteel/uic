/**
 *  @brief Store instruction class definition
 *
 *  @author Ammar Subei
*/

#include "ali.h"
#include "st.h"

void ST::execute(ALI &receiver)
{
  const std::string arg = std::to_string(receiver.getRegA());
  const int address = receiver.getSymbolAddress( getArgument() );
  
  ( receiver.getMemData(address) )->setType(Instruction::Type::NONE);
  ( receiver.getMemData(address) )->setArgument(arg);
}
