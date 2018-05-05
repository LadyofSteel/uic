/**
 *  @brief Load A instruction class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include "instruction.h"

class LDA : public Instruction
{
  public:
    /**
     *  @brief Default constructor
     *  @param string argument
    */
    LDA(std::string arg) : Instruction(Type::LDA, arg) {}

    /**
     *  @brief Implements instruction execution
     *  @param ALI instance
    */
    void execute(ALI &receiver) override;
};
