/**
 *  @brief Load B instruction class definition
 *
 *  @author Ammar Subei
*/

#include "ali.h"
#include "ldb.h"

void LDB::execute(ALI &receiver)
{
  const int address = receiver.getSymbolAddress( getArgument() );
  const int data = std::stoi( receiver.getMemData(address)->getArgument() );

  receiver.setRegB(data);

  // Increment program counter
  receiver.setPC( receiver.getPC() + 1 );
}
