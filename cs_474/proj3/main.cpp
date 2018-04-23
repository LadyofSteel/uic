/**
 *  @brief Main cpp file
 *
 *  @author Ammar Subei
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "appliancePtr.h"
#include "listNode.h"
#include "list.h"

void fileWrite(std::string filename)
{
  std::ofstream outFile;

  outFile.open(filename, std::ios::out | std::ios::trunc);

  if (outFile.is_open()) {
    outFile << "Overwrite something here" << std::endl;
    outFile.close();
  }
}

void fileRead(std::string filename)
{
  std::string line;
  std::ifstream inFile;

  inFile.open(filename);

  if (inFile.is_open()) {
    while ( getline(inFile, line) ) {
      // update object members
      std::cout << line << std::endl;
    }

    inFile.close();
  }
}

int main(int argc, char **argv)
{
  List<AppliancePtr> *list = new List<AppliancePtr>(10);

  list->at(0)->setID(1);
  std::cout << list->at(0)->getID();

  fileWrite("test.txt");
  fileRead("test.txt");

  return 0;
}
