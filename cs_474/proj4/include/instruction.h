/**
 *  @brief Instruction abstract class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include <iostream>
#include <string>

class ALI;

class Instruction
{
  public:
    /**
     *  @brief Default constructor
     *  @param string argument
    */
    enum class Type
    {
      NONE, ///< Not a command
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
     *  @param Type instruction type
     *  @param string argument
    */
    Instruction(Type t, std::string arg = "") : type(t), argument(arg) {}

    /**
     *  @brief Secondary constructor
     *  @param string instruction line
     *
     *  Creates Instruction object from instruction string.
     *  Implemented by derived classes.
    */
    Instruction(std::string);

    /**
     *  @brief Getter for instruction type
     *  @return Type type
    */
    Type getType()                    const { return type; }

    /**
     *  @brief Getter for instruction argument
     *  @return string argument
    */
    std::string getArgument()         const { return argument; }

    /**
     *  @brief Setter for instruction type
     *  @param Type type
    */
    void setType(const Type t)              { type = t; }

    /**
     *  @brief Setter for instruction argument
     *  @param string argument
    */
    void setArgument(const std::string arg) { argument = arg; }

    /**
     *  @brief Overloads outstream operator
     *  @param ostream& output stream
     *  @param Instruction& instruction object
     *  @return ostream& output stream
    */
    std::string toString() const
    {
      std::string command = "";

      // Convert Type enum to its string representation
      switch (getType()) {
        case Type::NONE: return getArgument();
        case Type::DEC: command = "DEC";  break;
        case Type::LDA: command = "LDA";  break;
        case Type::LDB: command = "LDB";  break;
        case Type::LDI: command = "LDI";  break;
        case Type::ST:  command = "ST";   break;
        case Type::XCH: command = "XCH";  break;
        case Type::JMP: command = "JMP";  break;
        case Type::JVS: command = "JVS";  break;
        case Type::JZS: command = "JZS";  break;
        case Type::ADD: command = "ADD";  break;
        case Type::HLT: command = "HLT";  break;
        default: break;
      }

      return (command + " " + getArgument());
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
