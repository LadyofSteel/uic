/**
 *  @brief Jump Overflow instruction class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include "instruction.h"

class JVS : public Instruction
{
  public:
    /**
     *  @brief Default constructor
     *  @param string argument
    */
    JVS(std::string arg) : Instruction(Type::JVS, arg) {}

    /**
     *  @brief Implements instruction execution
     *  @param ALI instance
    */
    void execute(ALI &receiver) override;
};
