#pragma once

#include "instruction.h"

class DEC : public Instruction
{
  public:
    DEC(std::string arg) : Instruction(Type::DEC, arg) {}

    void execute(ALI &receiver) override;
};
