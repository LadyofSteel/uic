#pragma once

#include "instruction.h"

class JVS : public Instruction
{
  public:
    JVS(std::string arg) : Instruction(Type::JVS, arg) {}

    void execute(ALI &receiver) override;
};
