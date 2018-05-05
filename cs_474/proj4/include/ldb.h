/**
 *  @brief Load B instruction class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include "instruction.h"

class LDB : public Instruction
{
  public:
    /**
     *  @brief Default constructor
     *  @param string argument
    */
    LDB(std::string arg) : Instruction(Type::LDB, arg) {}

    /**
     *  @brief Implements instruction execution
     *  @param ALI instance
    */
    void execute(ALI &receiver) override;
};
