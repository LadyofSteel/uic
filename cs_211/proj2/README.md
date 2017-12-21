# CS 211 Project 2

### Info
Using **C**, this project is a balanced symbol checker; it should determine whether input from user is given with properly balanced symbols. The symbols are "() {} [] <>". The project requires the use of a stack implemented as a dynamic array. For any unbalanced expressions, the program is required to report the missing symbol that causes the unbalance.

**Balanced Input**
- ( a b < c > )
- ( ) { a b [ c < > d ] }
- { }
**Unbalanced Input**
- ( a b < c )
- ( ) { a b [ c < > d ] } )
- { ) }
- (

### Usage
A makefile is provided for easier compilation. Enter `make` or `make proj2` to build the project. Enter `make run` to run the executable. If you want to build and run, just enter `make all`. If you want to build and run in debug mode, enter `make debug`.
Recompilation should work just fine with `make`, since the source files are set as dependencies for the build process.

For manual compilation, type `gcc -o proj2 main.c`. Then run the executable using `./proj2`.

To clean up, enter `make clean`.