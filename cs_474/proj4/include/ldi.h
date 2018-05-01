#pragma once

#include "instruction.h"

class LDI : public Instruction
{
  public:
    LDI(std::string arg) : Instruction(Type::LDI, arg) {}

    void execute(ALI &receiver) override;
};
