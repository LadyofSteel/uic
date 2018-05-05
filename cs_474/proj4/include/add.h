/**
 *  @brief Add instruction class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include "instruction.h"

class ADD : public Instruction
{
  public:
    ADD() : Instruction(Type::ADD) {}

    /**
     *  @brief Secondary constructor
     *  @param string instruction line
     *
     *  Creates Instruction object from instruction string.
    */
    // TODO
    //ADD(std::string line) : Instruction(Type::ADD) {}

    void execute(ALI &receiver) override;
};
