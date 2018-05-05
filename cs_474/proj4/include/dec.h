/**
 *  @brief Declare instruction class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include "instruction.h"

class DEC : public Instruction
{
  public:
    /**
     *  @brief Default constructor
     *  @param string argument
    */
    DEC(std::string arg) : Instruction(Type::DEC, arg) {}

    /**
     *  @brief Implements instruction execution
     *  @param ALI instance
    */
    void execute(ALI &receiver) override;
};
