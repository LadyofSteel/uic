/**
 *  @brief Main cpp file
 *
 *  @author Ammar Subei
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cctype>

#include "appliancePtr.h"
#include "list.h"

bool fileExists(std::string filename)
{
  std::ifstream file;
  file.open(filename);
  if (file) {
    file.close();
    return true;
  }

  return false;
}

void createApp(List<AppliancePtr> *list)
{
  int id;
  int type;
  double price;
  std::string man;
  std::string filesLine;
  std::vector<std::string> pics;

  std::cout << "Please enter the appliance ID: ";
  std::cin >> id;

  std::cout << "Please enter the appliance type ('0' for laundry machine,"
    << " '1' for dish washer, '2' for dryer): ";
  std::cin >> type;

  std::cout << "Please enter the appliance price (without commas): ";
  std::cin >> price;

  std::cout << "Please enter the appliance manufacturer name: ";
  std::cin >> man;

  std::cout << "Please enter the filepaths to the appliance images separated by commas: ";
  std::cin >> filesLine;

  char *temp = new char[filesLine.length() + 1];
  strcpy(temp, filesLine.c_str());
  char *token = strtok(temp, ",");

  while (token != NULL) {
    pics.push_back( std::string(token) );
    token = strtok(NULL, ",");
  }

  delete [] temp;

  list->at(id).create(id, type, man, price, pics);

  std::cout << "Appliance created!" << std::endl;
}

void listApps(List<AppliancePtr> *list)
{
  for (int i = 0; i < 10; i++) {
    std::string filename = "file" + std::to_string(i) + ".txt";
    if ( fileExists(filename) ) {
      list->at(i).print(i);
    } else {
      std::cout << "No information available for appliance with ID " << i << std::endl;
    }
  }
}

void editApp(List<AppliancePtr> *list, const int id)
{
  double newPrice;

  std::cout << "Please enter the new appliance price: ";
  std::cin >> newPrice;

  list->at(id).edit(newPrice);

  std::cout << "Updated appliance:" << std::endl;
  list->at(id).print(id);
}

void saveApps(List<AppliancePtr> *list, const int id)
{
  list->at(id).save();
  std::cout << "Appliances saved!" << std::endl;
}

int main(int argc, char **argv)
{
  List<AppliancePtr> *list = new List<AppliancePtr>(10);

  int currentID;
  char userInput;

  std::cout << "**** Appliance Manager ****" << std::endl << std::endl;
  std::cout << "Please enter your command: ";
  std::cin >> userInput;

  while(userInput != 'q') {
    if (userInput == 'c') {
      createApp(list);
    } else if (userInput == 'l') {
      listApps(list);
    } else if (userInput == 'p') {
      editApp(list, currentID);
    } else if (userInput == 's') {
      saveApps(list, currentID);
    } else if ( isdigit(userInput) ) {
      currentID = userInput - 48;
      if ( !list->at(currentID).setCurrent() ) {
        std::cout << "The specified appliance does not exist! Please create one." << std::endl;
      } else {
        std::cout << "Appliance with ID " << currentID << " is selected!" << std::endl;
      }
    } else {
      std::cout << "Invalid command! ";
    }

    std::cout << "Please enter your command: ";
    std::cin >> userInput;
  }

  std::cout << std::endl << "Good Bye!" << std::endl;
  delete list;
  return 0;
}
