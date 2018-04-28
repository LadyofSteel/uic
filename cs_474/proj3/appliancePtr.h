/**
 *  @brief AppliancePtr class header
 *
 *  @author Ammar Subei
 */

#pragma once

#include <queue>

#include "appliance.h"

class AppliancePtr
{
  public:
    /**
     *  @brief Default constructor
     */
    AppliancePtr() : appliance(new Appliance()) {}

    /**
     *  @brief Copy constructor
     */
    AppliancePtr(Appliance *a) : appliance(a) {}

    /**
     *  @brief Destructor
     */
    // TODO
    //~AppliancePtr()         { delete appliance; }

    /**
     *  @brief Dereference operator
     */
    Appliance& operator*()  { return *appliance; }

    /**
     *  @brief Arrow operator
     */
    Appliance* operator->() { return appliance; }

    bool setCurrent();

    void create(const int id, const int type, const std::string man,
        const double price, std::vector<std::string> pics);

    void edit(const double price);

    void save();

    void print(const int id);

    void release();

  private:
    void writeFile();

    bool readFile(const int id);

  protected:
    static std::queue<AppliancePtr> inMemory; ///< Appliances in memory
    Appliance *appliance;                     ///< Actual pointer to appliance
};
