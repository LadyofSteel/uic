/**
 *  @brief AppliancePtr class definitions
 *
 *  @author Ammar Subei
 */

#include <iostream>
#include <fstream>
#include <cstring>

#include "appliancePtr.h"

// Explicit definition of static member
std::queue<AppliancePtr> AppliancePtr::inMemory;

void AppliancePtr::writeFile()
{
  const int id = appliance->getID();
  const double price = appliance->getPrice();
  const std::string man = appliance->getManufacturer();
  std::vector<std::string> pics = appliance->getImages();

  int type = 0;
  switch (appliance->getType()) {
    case Appliance::Type::LAUNDRY_MACHINE:
      type = 0;
      break;

    case Appliance::Type::DISH_WASHER:
      type = 1;
      break;

    case Appliance::Type::DRYER:
      type = 2;
      break;

    default:
      break;
  }

  std::string outFileName = "file" + std::to_string(id) + ".txt";
  std::ofstream outFile;
  outFile.open(outFileName, std::ios::out | std::ios::trunc);

  if (outFile.is_open()) {
    outFile << id << std::endl << type << std::endl
      << man << std::endl << price << std::endl;

    for (auto filepath : pics) {
      outFile << filepath << ",";
    }
  }

  outFile.close();
}

bool AppliancePtr::readFile(const int id)
{
  std::string inFileName = "file" + std::to_string(id) + ".txt";                                    
  std::ifstream inFile;                                                                               
  inFile.open(inFileName);                                                                            
  if (!inFile) {                                                                                      
    return false;
  } else {
    std::string line;

    // Read appliance ID
    getline(inFile, line);
    appliance->setID(std::stoi(line));

    // Read appliance type
    getline(inFile, line);
    switch (std::stoi(line)) {
      case 0:
        appliance->setType(Appliance::Type::LAUNDRY_MACHINE);
        break;

      case 1:
        appliance->setType(Appliance::Type::DISH_WASHER);
        break;

      case 2:
        appliance->setType(Appliance::Type::DRYER);
        break;

      default:
        break;
    }

    // Read appliance manufacturer
    getline(inFile, line);
    appliance->setManufacturer(line);

    // Read appliance price
    getline(inFile, line);
    appliance->setPrice(std::stod(line));

    // Read appliance image filepaths
    getline(inFile, line);

    std::vector<std::string> tempPics;
    char *temp = new char[line.length() + 1];
    strcpy(temp, line.c_str());
    char *token = strtok(temp, ",");

    while (token != NULL) {
      tempPics.push_back( std::string(token) );
      token = strtok(NULL, ",");
    }

    appliance->setImages(tempPics);
    delete [] temp;
  }

  inFile.close();
  return true;
}

bool AppliancePtr::setCurrent()
{
  if ( AppliancePtr::inMemory.size() >= 3 ) {
    AppliancePtr::inMemory.front().release();
    AppliancePtr::inMemory.pop();
  }

  if ( !readFile(appliance->getID()) ) {
    return false;
  }

  AppliancePtr::inMemory.push(*this);
  return true;
}

void AppliancePtr::create(const int id, const int type, const std::string man,
    const double price, std::vector<std::string> pics)
{
  if ( AppliancePtr::inMemory.size() >= 3 ) {
    AppliancePtr::inMemory.front().release();
    AppliancePtr::inMemory.pop();
  }

  appliance->setID(id);
  appliance->setManufacturer(man);
  appliance->setPrice(price);
  appliance->setImages(pics);
  
  switch (type) {
    case 0:
      appliance->setType(Appliance::Type::LAUNDRY_MACHINE);
      break;

    case 1:
      appliance->setType(Appliance::Type::DISH_WASHER);
      break;

    case 2:
      appliance->setType(Appliance::Type::DRYER);
      break;

    default:
      break;
  }

  writeFile();

  AppliancePtr::inMemory.push(*this);
}

void AppliancePtr::edit(const double price)
{
  appliance->setPrice(price);
}

void AppliancePtr::save()
{
  std::queue<AppliancePtr> temp = AppliancePtr::inMemory;
  while (!temp.empty()) {
    temp.front().writeFile();
    temp.pop();
  }
}

void AppliancePtr::print(const int id)
{
  std::string type= "";
  std::string filePaths = "";

  switch (appliance->getType()) {
    case Appliance::Type::LAUNDRY_MACHINE:
      type = "Laundry Machine";
      break;

    case Appliance::Type::DISH_WASHER:
      type = "Dish Washer";
      break;

    case Appliance::Type::DRYER:
      type = "Dryer";
      break;

    default:
      break;
  }

  for (auto path : appliance->getImages()) {
    filePaths.append(path);
    filePaths.append(" ");
  }

  std::cout << "Information for appliance with ID " << id << ":" << std::endl;
  std::cout << "Type: " << type << std::endl;
  std::cout << "Price: " << appliance->getPrice() << std::endl;
  std::cout << "Manufacturer: " << appliance->getManufacturer() << std::endl;
  std::cout << "Image file paths: " << filePaths << std::endl;
}

void AppliancePtr::release()
{
  appliance = nullptr;
}
