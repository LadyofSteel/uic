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
  
  receiver.setRegB( receiver.getRegA() );
  receiver.setRegA(temp);

  receiver.setPC( receiver.getPC() + 1 );
}
