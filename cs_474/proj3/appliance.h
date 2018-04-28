/**
 *  @brief Appliance class header
 *
 *  @author Ammar Subei
 */

#pragma once

#include <vector>
#include <string>

class Appliance
{
  public:
    /**
     *  @brief Enum for type of appliance
     */
    enum class Type
    {
      LAUNDRY_MACHINE,  ///< Laundry machine
      DISH_WASHER,      ///< Dish washer
      DRYER             ///< Dryer
    };

    /**
     *  @brief Getter for type of appliance
     *
     *  @return Type type of appliance
     */
    Appliance::Type getType()                 const { return type; }

    /**
     *  @brief Getter for appliance ID
     *
     *  @return int appliance ID
     */
    int getID()                               const { return id; }

    /**
     *  @brief Getter for appliance price
     *
     *  @return double appliance price
     */
    double getPrice()                         const { return price; }

    /**
     *  @brief Getter for appliance manufacturer
     *
     *  @return string appliance manufacturer
     */
    std::string getManufacturer()             const { return manufacturer; }

    /**
     *  @brief Getter for appliance images
     *
     *  @return vector<string> appliance images
     */
    std::vector<std::string> getImages()      const { return images; }

    /**
     *  @brief Setter for type of appliance
     *
     *  @param Type new type
     */
    void setType(const Appliance::Type t)           { type = t; }

    /**
     *  @brief Setter for appliance ID
     *
     *  @param int new ID
     */
    void setID(const int newID)                     { id = newID; }

    /**
     *  @brief Setter for appliance price
     *
     *  @param int new price
     */
    void setPrice(const double newPrice)            { price = newPrice; }

    /**
     *  @brief Setter for appliance manufacturer
     *
     *  @param string new manufacturer name
     */
    void setManufacturer(const std::string newMan)  { manufacturer = newMan; }

    /**
     *  @brief Setter for appliance images
     *
     *  @param vector<string> images
     */
    void setImages(std::vector<std::string> pics)        { images = pics; }

  protected:
    Type type;                        ///< Appliance's type
    int id;                           ///< Appliance's ID
    double price;                     ///< Appliance's price
    std::string manufacturer;         ///< Appliance's manufacturer
    std::vector<std::string> images;  ///< Appliance images
};
