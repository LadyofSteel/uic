/**
 *  @brief Load Integer instruction class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include "instruction.h"

class LDI : public Instruction
{
  public:
    /**
     *  @brief Default constructor
     *  @param string argument
    */
    LDI(std::string arg) : Instruction(Type::LDI, arg) {}

    /**
     *  @brief Implements instruction execution
     *  @param ALI instance
    */
    void execute(ALI &receiver) override;
};
