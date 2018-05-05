/**
 *  @brief Exchange instruction class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include "instruction.h"

class XCH : public Instruction
{
  public:
    /**
     *  @brief Default constructor
    */
    XCH() : Instruction(Type::XCH) {}

    /**
     *  @brief Implements instruction execution
     *  @param ALI instance
    */
    void execute(ALI &receiver) override;
};
