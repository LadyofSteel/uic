/**
 *  @brief Interface class header file
 *
 *  @author Ammar Subei
*/

#pragma once

// Forward declaration of class ALI
class ALI;

class Interface
{
  public:
    /**
     *  @brief Default constructor
    */
    Interface() : ali(new ALI()) {}

    /**
     *  @brief Prints the current state of ALI
    */
    void printState();

    /**
     *  @brief Runs user input commands
    */
    void runCommands();

  private:
    /**
     *  @brief Runs one line of SAL code
     *  @return bool program ended
    */
    bool runDebug();

    /**
     *  @brief Runs entire SAL program
     *  @return bool program ended
    */
    bool runAll();

    /**
     *  @brief Reads SAL program from input.sal
     *  @return bool read successful
    */
    bool readFile();

    /**
     *  @brief Saves current ALI state to output.txt
    */
    void saveFile();

    /**
     *  @brief Prints contents of ALI memory
    */
    void printMemory();

    /**
     *  @brief Prints contents of ALI registers
    */
    void printRegisters();
    
    /**
     *  @brief Prints contents of ALI bits
    */
    void printBits();

  private:
    ALI *ali; ///< ALI instance pointer
};
