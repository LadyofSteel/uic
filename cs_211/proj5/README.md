# CS 211 Project 5

### Info
Using **C++**, this project should evaluate an infix expression. The algorithm **required** for this program will use two stacks, an operator stack and a value stack. Both stacks must be implemented using a dynamic array class. The infix expression will only use the operators of addition, subtraction, multiplication, division, and parentheses.

### Usage
A makefile is provided for easier compilation. Enter `make` or `make proj5` to build the project. Enter `make run` to run the executable. If you want to build and run, just enter `make all`. If you want to build and run in debug mode, enter `make debug`.
Recompilation should work just fine with `make`; the source and header files are set as dependencies for the build process.

To clean up, enter `make clean`.

### Notes
I have made some minor modifications in the Tokens class files only to resolve the compiler warnings (it was about comparing signed with unsigned integers). Also, I wrote a templated class because it seemed easier to handle and write than using enums with if-statements everywhere.