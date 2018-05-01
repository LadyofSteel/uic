#pragma once

#include "instruction.h"

class JZS : public Instruction
{
  public:
    JZS(std::string arg) : Instruction(Type::JZS, arg) {}

    void execute(ALI &receiver) override;
};
