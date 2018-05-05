/**
 *  @brief Load A instruction class definition
 *
 *  @author Ammar Subei
*/

#include "ali.h"
#include "lda.h"

void LDA::execute(ALI &receiver)
{
  const int address = receiver.getSymbolAddress( getArgument() );
  const int data = std::stoi( receiver.getMemData(address)->getArgument() );

  receiver.setRegA(data);

  // Increment program counter
  receiver.setPC( receiver.getPC() + 1 );
}
