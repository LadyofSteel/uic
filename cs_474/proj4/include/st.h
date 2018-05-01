#pragma once

#include "instruction.h"

class ST : public Instruction
{
  public:
    ST(std::string arg) : Instruction(Type::ST, arg) {}

    void execute(ALI &receiver) override;
};
