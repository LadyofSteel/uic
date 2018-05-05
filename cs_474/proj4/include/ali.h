/**
 *  @brief ALI class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include <unordered_map>
#include <vector>

#include "instruction.h"

class ALI
{
  public:
    /**
     *  @brief Default constructor
    */
    ALI() : regA(0), regB(0), pc(0), zero(false),
    overflow(false) {}

    /**
     *  @brief Getter for Register A
     *  @return int regA
    */
    int getRegA()                 const { return regA; }

    /**
     *  @brief Getter for Register B
     *  @return int regB
    */
    int getRegB()                 const { return regB; }

    /**
     *  @brief Getter for program counter
     *  @return int pc
    */
    int getPC()                   const { return pc; }

    /**
     *  @brief Getter for halt status
     *  @return bool halt
    */
    bool isHalted()               const { return halt; }

    /**
     *  @brief Getter for zero bit
     *  @return bool zero bit
    */
    bool isZero()                 const { return zero; }

    /**
     *  @brief Getter for overflow bit
     *  @return bool overflow bit
    */
    bool isOverflow()             const { return overflow; }

    /**
     *  @brief Setter for Register A
     *  @param int new value
    */
    void setRegA(const int value)       { regA = value; }

    /**
     *  @brief Setter for Register B
     *  @param int new value
    */
    void setRegB(const int value)       { regB = value; }

    /**
     *  @brief Setter for program counter
     *  @param int new value
    */
    void setPC(const int value)         { pc = value; }

    /**
     *  @brief Setter for halt status
     *  @param bool new value
    */
    void setHalt(const bool value)      { halt = value; }

    /**
     *  @brief Setter for zero bit
     *  @param bool new value
    */
    void setZero(const bool value)      { zero = value; }

    /**
     *  @brief Setter for overflow bit
     *  @param bool new value
    */
    void setOverflow(const bool value)  { overflow = value; }

    /**
     *  @brief Getter for data at memory address
     *  @param int address
     *  @return Instruction* instruction
    */
    Instruction* getMemData(const int address) const;

    /**
     *  @brief Getter for data at memory address
     *  @param int address
    */
    int getSymbolAddress(const std::string symbol) const;

    /**
     *  @brief Adds data to memory
     *  @param string data
    */
    void addMemData(std::string data);

    /**
     *  @brief Adds symbol and its address to symTable
     *  @param string symbol
     *  @param int symbol's address
    */
    void addSymbol(const std::string symbol, const int address);

  private:
    int regA;
    int regB;
    int pc;
    bool halt;
    bool zero;
    bool overflow;
    std::vector<Instruction*> memory;
    std::unordered_map<std::string, int> symTable;
};
