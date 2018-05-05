/**
 *  @brief ALI class definitions
 *
 *  @author Ammar Subei
*/

#include <sstream>

#include "ali.h"
#include "commandIncludes.h"

Instruction* ALI::getMemData(const int address) const
{
  if (address < memory.size()) {
    return memory.at(address);
  } else {
    return nullptr;
  }
}

int ALI::getSymbolAddress(const std::string symbol) const
{
  return symTable.at(symbol);
}

void ALI::addMemData(std::string data)
{
  // Use stringstream to tokenize instruction line
  std::stringstream ss(data);

  std::string command;
  std::string arg;

  std::getline(ss, command, ' ');
  std::getline(ss, arg);

  // Add the right instruction to memory
  if (command == "DEC") {
    memory.push_back( new DEC(arg) );
  } else if (command == "LDA") {
    memory.push_back( new LDA(arg) );
  } else if (command == "LDB") {
    memory.push_back( new LDB(arg) );
  } else if (command == "LDI") {
    memory.push_back( new LDI(arg) );
  } else if (command == "ST") {
    memory.push_back( new ST(arg) );
  } else if (command == "JMP") {
    memory.push_back( new JMP(arg) );
  } else if (command == "JVS") {
    memory.push_back( new JVS(arg) );
  } else if (command == "JZS") {
    memory.push_back( new JZS(arg) );
  } else if (command == "ADD") {
    memory.push_back( new ADD() );
  } else if (command == "XCH") {
    memory.push_back( new XCH() );
  } else if (command == "HLT") {
    memory.push_back( new HLT() );
  } else {
    return;
  }
}

void ALI::addSymbol(const std::string data, const int address)
{
  symTable.insert( std::make_pair(data, address) );
}
