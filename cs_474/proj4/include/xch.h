#pragma once

#include "instruction.h"

class XCH : public Instruction
{
  public:
    XCH() : Instruction(Type::XCH) {}

    void execute(ALI &receiver) override;
};
