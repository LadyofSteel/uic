#include "ali.h"
#include "interface.h"
#include "commandIncludes.h"

int main()
{
  Interface *ui = new Interface();

  std::cout << std::endl;
  std::cout << "Simple Assembly Language Interpreter" << std::endl;
  std::cout << "Developed by Ammar Subei" << std::endl;
  std::cout << std::endl;

  ui->runCommands();

  std::cout << std::endl;
  std::cout << "Exiting program..." << std::endl;
  std::cout << "Goodbye!" << std::endl;

  return 0;
}
