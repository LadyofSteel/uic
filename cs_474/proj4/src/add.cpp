/**
 *  @brief Add instruction class definition
 *
 *  @author Ammar Subei
*/

#include "ali.h"
#include "add.h"

void ADD::execute(ALI &receiver)
{
  const int a = receiver.getRegA();
  const int b = receiver.getRegB();
  int sum = a + b;

  // Set zero bit as needed
  receiver.setZero( sum == 0 );

  // Set overflow bit as needed
  if (sum > 536870911) {
    sum -= 536870911;
    receiver.setOverflow(true);
  } else if (sum < -536870912) {
    sum += 536870912;
    receiver.setOverflow(true);
  } else {
    receiver.setOverflow(false);
  }

  receiver.setRegA(sum);

  // Increment program counter
  receiver.setPC( receiver.getPC() + 1 );
}
