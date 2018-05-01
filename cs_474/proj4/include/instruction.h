/**
 *  @brief Instruction abstract class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include <iostream>
#include <string>

#include "ali.h"

class Instruction
{
  public:
    /**
     *  @brief Default constructor
     *  @param string argument
    */
    enum class Type
    {
      DEC,  ///< Declare command
      LDA,  ///< Load A command
      LDB,  ///< Load B command
      LDI,  ///< Load int command
      ST,   ///< Store command
      XCH,  ///< Exchange command
      JMP,  ///< Jump command
      JVS,  ///< Jump overflow command
      JZS,  ///< Jump zero command
      ADD,  ///< Add command
      HLT   ///< Halt command
    };

    /**
     *  @brief Default constructor
     *  @param string argument
    */
    Instruction(Type t, std::string arg = "") : type(t), argument(arg) {}

    /**
     *  @brief Getter for instruction type
     *  @return Type type
    */
    Type getType()            const { return type; }

    /**
     *  @brief Getter for instruction argument
     *  @return string argument
    */
    std::string getArgument() const { return argument; }

    /**
     *  @brief Overloads outstream operator
     *  @param ostream& output stream
     *  @param Instruction& instruction object
     *  @return ostream& output stream
    */
    friend std::ostream& operator<<(std::ostream &os, const Instruction &instr)
    {
      std::string command = "";

      // Convert Type enum to its string representation
      switch (instr.getType()) {
        case Type::DEC: command = "DEC"; break;
        case Type::LDA: command = "LDA"; break;
        case Type::LDB: command = "LDB"; break;
        case Type::LDI: command = "LDI"; break;
        case Type::ST: command = "ST"; break;
        case Type::XCH: command = "XCH"; break;
        case Type::JMP: command = "JMP"; break;
        case Type::JVS: command = "JVS"; break;
        case Type::JZS: command = "JZS"; break;
        case Type::ADD: command = "ADD"; break;
        case Type::HLT: command = "HLT"; break;
        default: break;
      }

      os << command << " " << instr.getArgument() << std::endl;
      return os;
    }

    /**
     *  @brief Execute instruction
     *  @param ALI interpreter object
    */
    virtual void execute(ALI &reciever) = 0;

  private:
    Type type;            ///< Instruction's type
    std::string argument; ///< Instruction's argument
};
