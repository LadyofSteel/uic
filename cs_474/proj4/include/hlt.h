#pragma once

#include "instruction.h"

class HLT : public Instruction
{
  public:
    HLT() : Instruction(Type::HLT) {}

    void execute(ALI &receiver) override;
};
