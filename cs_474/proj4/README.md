# CS 474 Project 4

### Info
Using **C++11**, this project is a Simple Assembly Language Interpreter. The program uses the command line as the user interface. It can only interpret SAL code from an `input.sal` file in the executable directory.

### Usage
A makefile is provided for easier compilation. Enter `make` or `make proj4` to build the project. Enter `make run` to run the executable. If you want to build and run, just enter `make all`.
Recompilation should work just fine with `make`, the source and header files are set as dependencies for the build process.

To clean up, enter `make clean`.

The user interface is very simple and self-explanatory.

### Notes
It is crucial that the SAL program is valid and **ALWAYS** ends with the `HLT` instruction. To avoid possible issues, try not to have any trailing whitespace or empty lines in the input SAL file.
