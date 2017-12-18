/**
 *  @brief Main file
 *
 *  Main file for final exam program for CS 211.
 *
 *  @author Ammar Subei
 *  @date Wednesday Dec. 6th, 2017
*/

#include <iostream>

#include "myList.h"

void doAdd(MyList<int> **sets, const int set, const int value)
{
  sets[set - 1]->add(value);
}

void doPrint(MyList<int> **sets, const int set)
{
  sets[set - 1]->showList();
}

void doRemove(MyList<int> **sets, const int set)
{
  sets[set - 1]->removeAll();
}

void doUnion(MyList<int> **sets, const int resultSet, const int inSet1, const int inSet2)
{
  MyList<int> *targetSet = sets[resultSet - 1];
  MyList<int> *set1 = sets[inSet1 - 1];
  MyList<int> *set2 = sets[inSet2 - 1];

  targetSet->removeAll();

  // Adds non-duplicates from set1
  for (int i = 0; i < set1->getLength(); i++) {
    const int x = set1->getNthValue(i);

    if ( !targetSet->doesValueExist(x) ){
      targetSet->add(x);
    }
  }

  // Adds non-duplicates from set2
  for (int i = 0; i < set2->getLength(); i++) {
    const int x = set2->getNthValue(i);

    if ( !targetSet->doesValueExist(x) ){
      targetSet->add(x);
    }
  }
}

void doIntersect(MyList<int> **sets, const int resultSet, const int inSet1, const int inSet2)
{
  MyList<int> *targetSet = sets[resultSet - 1];
  MyList<int> *set1 = sets[inSet1 - 1];
  MyList<int> *set2 = sets[inSet2 - 1];

  targetSet->removeAll();

  // Adds non-duplicates common to set1 and set2
  for (int i = 0; i < set1->getLength(); i++) {
    const int x = set1->getNthValue(i);

    if ( set2->doesValueExist(x) ){
      if ( !targetSet->doesValueExist(x) ){
        targetSet->add(x);
      }
    }
  }
}

void runCommands(MyList<int> **sets)
{
  int command = 0;

  while (true) {
    std::cin >> command;

    if (command == -1) {
      int input1 = 0;
      int input2 = 0;

      std::cin >> input1 >> input2;

      if ( (input1 < 1 || input1 > 5) ) {
        std::cout << "Invalid set number " << input1 << ", please try again." << std::endl;
        continue;
      }

      std::cout << "Adding value " << input2 << " to set " << input1 << std::endl;

      doAdd(sets, input1, input2);
    } else if (command == -2) {
      int input1 = 0;

      std::cin >> input1;

      if ( (input1 < 1 || input1 > 5) ) {
        std::cout << "Invalid set number " << input1 << ", please try again." << std::endl;
        continue;
      }

      std::cout << "Printing values of set " << input1 << std::endl;

      doPrint(sets, input1);
    } else if (command == -3) {
      int input1 = 0;

      std::cin >> input1;

      if ( (input1 < 1 || input1 > 5) ) {
        std::cout << "Invalid set number " << input1 << ", please try again." << std::endl;
        continue;
      }

      std::cout << "Deleting the set " << input1 << std::endl;

      doRemove(sets, input1);
    } else if (command == -4) {
      int input1 = 0;
      int input2 = 0;
      int input3 = 0;

      std::cin >> input1 >> input2 >> input3;

      if ( (input1 < 1 || input1 > 5) ) {
        std::cout << "Invalid set number " << input1 << ", please try again." << std::endl;
        continue;
      } else if ( (input2 < 1 || input2 > 5) ) {
        std::cout << "Invalid set number " << input2 << ", please try again." << std::endl;
        continue;
      } else if ( (input3 < 1 || input3 > 5) ) {
        std::cout << "Invalid set number " << input3 << ", please try again." << std::endl;
        continue;
      }

      std::cout << "Storing union of sets " << input2 << " and " << input3
        << " into set " << input1 << std::endl;

      doUnion(sets, input1, input2, input3);
    } else if (command == -5) {
      int input1 = 0;
      int input2 = 0;
      int input3 = 0;

      std::cin >> input1 >> input2 >> input3;

      if ( (input1 < 1 || input1 > 5) ) {
        std::cout << "Invalid set number " << input1 << ", please try again." << std::endl;
        continue;
      } else if ( (input2 < 1 || input2 > 5) ) {
        std::cout << "Invalid set number " << input2 << ", please try again." << std::endl;
        continue;
      } else if ( (input3 < 1 || input3 > 5) ) {
        std::cout << "Invalid set number " << input3 << ", please try again." << std::endl;
        continue;
      }

      std::cout << "Storing intersection of sets " << input2 << " and " << input3
        << " into set " << input1 << std::endl;

      doIntersect(sets, input1, input2, input3);
    } else if (command == -6) {
      std::cout << "Exiting the program" << std::endl;
      return;
    } else {
      std::cout << "Invalid command, please try again." << std::endl;
    }
  }
}

int main(int argc, char **argv)
{
  int setCount = 5;

  MyList<int> **sets = new MyList<int>*[setCount];
  for (int i = 0; i < setCount; i++) {
    sets[i] = new MyList<int>();
  }

  std::cout << "Program for Exam2 is starting!" << std::endl;

  runCommands(sets);
  return 0;
}
