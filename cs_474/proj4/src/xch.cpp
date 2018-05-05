/**
 *  @brief Exchange instruction class definition
 *
 *  @author Ammar Subei
*/

#include "ali.h"
#include "xch.h"

void XCH::execute(ALI &receiver)
{
  const int temp = receiver.getRegB();
  
  // Swap registers
  receiver.setRegB( receiver.getRegA() );
  receiver.setRegA(temp);

  // Increment program counter
  receiver.setPC( receiver.getPC() + 1 );
}
