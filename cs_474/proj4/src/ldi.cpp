/**
 *  @brief Load int instruction class definition
 *
 *  @author Ammar Subei
*/

#include "ali.h"
#include "ldi.h"

void LDI::execute(ALI &receiver)
{
  receiver.setRegA( std::stoi(getArgument()) );

  receiver.setPC( receiver.getPC() + 1 );
}
