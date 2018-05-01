#pragma once

#include "instruction.h"

class JMP : public Instruction
{
  public:
    JMP(std::string arg) : Instruction(Type::JMP, arg) {}

    void execute(ALI &receiver) override;
};
