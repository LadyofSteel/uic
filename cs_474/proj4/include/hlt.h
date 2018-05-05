/**
 *  @brief Halt instruction class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include "instruction.h"

class HLT : public Instruction
{
  public:
    /**
     *  @brief Default constructor
    */
    HLT() : Instruction(Type::HLT) {}

    /**
     *  @brief Implements instruction execution
     *  @param ALI instance
    */
    void execute(ALI &receiver) override;
};
