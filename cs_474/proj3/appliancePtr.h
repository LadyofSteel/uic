/**
 *  @brief AppliancePtr class header
 *
 *  @author Ammar Subei
 */

#pragma once

#include "appliance.h"

class AppliancePtr
{
  public:
    /**
     *  @brief Default constructor
     */
    AppliancePtr() : appliance(new Appliance()) {}

    /**
     *  @brief Destructor
     */
    ~AppliancePtr() {}

    Appliance& operator*()  { return *appliance; }

    Appliance* operator->() { return appliance; }

  protected:
    Appliance *appliance;
    static int inMemory; ///< Number of appliances loaded in memory
};

// Explicit definition of static member
int AppliancePtr::inMemory;
