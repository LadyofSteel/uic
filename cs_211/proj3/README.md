# CS 211 Project 3

Due date: Tuesday, Oct. 10th

### Info
Using **C**, this project should find its way through a maze using a depth-first search algorithm. The program takes input from a file where the filename is specified in the command line arguments. The input file will only contain two integer values per line of input:

- The first valid line gives the size of the 2-D maze
- The second valid line gives the coordinates of the starting position in the maze
- The third valid line gives the coordinates of the ending position in the maze
- The remaining valid lines in the file give the coordinates of blocked positions in the maze

Sample input files/mazes can be found in the repo. The program is to output each position of the path, which is **NOT** expected to be optimal.

### Usage
A makefile is provided for easier compilation. Enter `make` or `make proj3` to build the project. Enter `make run` to run the executable with an input file named `input1.txt`. If you want to build and run, just enter `make all`. If you want to build and run in debug mode, enter `make debug` (which runs with input file `input1.txt`).
Recompilation should work just fine with `make`, since the source files are set as dependencies for the build process.

For manual compilation, type `gcc -g -o proj3 stack.c maze.c main.c`. Then run the executable using `./proj3 <input_file>` or `./proj3 -d <input_file>`.

To clean up, enter `make clean`.