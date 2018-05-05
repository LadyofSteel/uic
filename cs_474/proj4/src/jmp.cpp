/**
 *  @brief Jump instruction class definition
 *
 *  @author Ammar Subei
*/

#include "ali.h"
#include "jmp.h"

void JMP::execute(ALI &receiver)
{
  receiver.setPC( std::stoi(getArgument()) );
}
