/**
 *  @brief Jump Zero instruction class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include "instruction.h"

class JZS : public Instruction
{
  public:
    /**
     *  @brief Default constructor
     *  @param string argument
    */
    JZS(std::string arg) : Instruction(Type::JZS, arg) {}

    /**
     *  @brief Implements instruction execution
     *  @param ALI instance
    */
    void execute(ALI &receiver) override;
};
