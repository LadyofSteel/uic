/**
 *  @brief Jump instruction class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include "instruction.h"

class JMP : public Instruction
{
  public:
    /**
     *  @brief Default constructor
     *  @param string argument
    */
    JMP(std::string arg) : Instruction(Type::JMP, arg) {}

    /**
     *  @brief Implements instruction execution
     *  @param ALI instance
    */
    void execute(ALI &receiver) override;
};
