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
    ADD() : Instruction(Type::ADD) {}

    void execute(ALI &receiver) override;
};
