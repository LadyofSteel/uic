/**
 *  @brief Store instruction class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include "instruction.h"

class ST : public Instruction
{
  public:
    /**
     *  @brief Default constructor
     *  @param string argument
    */
    ST(std::string arg) : Instruction(Type::ST, arg) {}

    /**
     *  @brief Implements instruction execution
     *  @param ALI instance
    */
    void execute(ALI &receiver) override;
};
