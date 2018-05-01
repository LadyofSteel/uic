#pragma once

#include "instruction.h"

class LDA : public Instruction
{
  public:
    LDA(std::string arg) : Instruction(Type::LDA, arg) {}

    void execute(ALI &receiver) override;
};
