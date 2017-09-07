# CS 211 Project 1

Due date: Monday, Sept. 11th

### Usage
A makefile is provided for easier compilation. Enter `make` or `make proj1` to build the project. Enter `make run` to run the executable. If you want to build and run, just enter `make all`.
Recompilation should work just fine with `make`, since the source files are set as dependencies for the build process.

For manual compilation, type `gcc -o proj1 main.c`. Then run the executable using `./proj1`.

To clean up, enter `make clean`.

##### Redirection
If you wish to use any input files using redirection, the `make` commands will still work fine. So you can just enter `make all < input1.txt` and the program will compile and run using `input1.txt` as the input for the executable.

If anything, just manually run the executable with redirection by typing `./proj1 < input1.txt`.