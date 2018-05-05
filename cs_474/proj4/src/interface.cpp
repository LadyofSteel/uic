/**
 *  @brief Interface class definitions
 *
 *  @author Ammar Subei
*/

#include <fstream>
#include <iostream>

#include "ali.h"
#include "interface.h"
#include "commandIncludes.h"

bool Interface::runDebug()
{
  // Program ended
  if (ali->isHalted()) {
    return true;
  }

  const int pc = ali->getPC();
  Instruction *instr = ali->getMemData(pc);

  // Check if mem data is valid
  if (!instr) {
    return true;
  }

  instr->execute(*ali);
  printState();
  return false;
}

bool Interface::runAll()
{
  // Program ended
  if (ali->isHalted()) {
    return true;
  }

  int pc = ali->getPC();

  while ( !ali->isHalted() ) {
    Instruction *instr = ali->getMemData(pc);
    if (!instr) {
      return true;
    }

    instr->execute(*ali);
    pc = ali->getPC();
  }

  // Program ended
  printState();
  return true;
}

bool Interface::readFile()
{
  // First reset ALI state and contents
  ali->reset();

  // Store each instruction line from input.sal to ALI memory
  std::string line = "";
  std::string filename = "input.sal";

  std::ifstream inFile(filename);

  if (inFile) {
    while ( std::getline(inFile, line) ) {
      ali->addMemData(line);
    }
  } else {
    return false;
  }

  inFile.close();
  return true;
}

void Interface::saveFile()
{
  std::string filename = "output.txt";

  std::ofstream outFile(filename, std::ios::trunc);

  outFile << "PROGRAM MEMORY" << std::endl;

  int counter = 0;
  Instruction *instr = ali->getMemData(counter);

  while (instr) {
    outFile << instr->toString() << std::endl;
    instr = ali->getMemData(++counter);
  }

  outFile << "--------------------" << std::endl;
  outFile << "PROGRAM REGISTERS" << std::endl;

  outFile << "Program Counter: " << ali->getPC() << std::endl;
  outFile << "Register A: " << ali->getRegA() << std::endl;
  outFile << "Register B: " << ali->getRegB() << std::endl;

  outFile << "--------------------" << std::endl;
  outFile << "PROGRAM BITS" << std::endl;

  outFile << "Zero Bit: " << ali->isZero() << std::endl;
  outFile << "Overflow Bit: " << ali->isOverflow() << std::endl;

  outFile.close();
}

void Interface::printMemory()
{
  int counter = 0;
  Instruction *instr = ali->getMemData(counter);

  std::cout << std::endl;
  std::cout << "********************" << std::endl;
  std::cout << "PROGRAM MEMORY" << std::endl;

  while (instr) {
    std::cout << instr->toString() << std::endl;
    instr = ali->getMemData(++counter);
  }
}

void Interface::printRegisters()
{
  std::cout << std::endl;
  std::cout << "********************" << std::endl;
  std::cout << "PROGRAM REGISTERS" << std::endl;

  std::cout << "Program Counter: " << ali->getPC() << std::endl;
  std::cout << "Register A: " << ali->getRegA() << std::endl;
  std::cout << "Register B: " << ali->getRegB() << std::endl;
}

void Interface::printBits()
{
  std::cout << std::endl;
  std::cout << "********************" << std::endl;
  std::cout << "PROGRAM BITS" << std::endl;

  std::cout << "Zero Bit: " << ali->isZero() << std::endl;
  std::cout << "Overflow Bit: " << ali->isOverflow() << std::endl;
}

void Interface::printState()
{
  printMemory();
  printRegisters();
  printBits();
}

void Interface::runCommands()
{
  char userInput;

  std::cout << "Please enter your desired commands." << std::endl;

  while (true) {
    std::cout << std::endl;
    std::cin >> userInput;

    if (userInput == 'q') {
      break;
    } else if (userInput == 'i') {

      if ( !readFile() ) {
        std::cout << "Error reading file! "
          << "Please make sure input.sal exists!" << std::endl;

        break;
      }

      std::cout << "Input file successfully read. "
        << "Your SAL program is ready!" << std::endl;

    } else if (userInput == 's') {
      saveFile();
    } else if (userInput == 'd') {
      if ( runDebug() ) {
        std::cout << "Program execution ended." << std::endl;
      }
    } else if (userInput == 'r') {
      if ( runAll() ) {
        std::cout << "Program execution ended." << std::endl;
      }
    } else {
      std::cout << "Invalid command. Try again!" << std::endl;
    }
  }
}
