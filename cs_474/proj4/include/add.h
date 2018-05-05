/**
 *  @brief Add instruction class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include "instruction.h"

class ADD : public Instruction
{
  public:
    /**
     *  @brief Default constructor
    */
    ADD() : Instruction(Type::ADD) {}

    /**
     *  @brief Implements instruction execution
     *  @param ALI instance
    */
    void execute(ALI &receiver) override;
};
