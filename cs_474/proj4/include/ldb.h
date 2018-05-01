#pragma once

#include "instruction.h"

class LDB : public Instruction
{
  public:
    LDB(std::string arg) : Instruction(Type::LDB, arg) {}

    void execute(ALI &receiver) override;
};
