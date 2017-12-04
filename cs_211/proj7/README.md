# CS 211 Project 7

Due date: Monday, Dec. 4th

### Usage
A makefile is provided for easier compilation. Enter `make` or `make proj7` to build the project. Enter `make run` to run the executable. If you want to build and run, just enter `make all`. If you want to build and run in debug mode, enter `make debug DELAY=<delay_value>`. Note that you need to specify the delay value when running in debug mode, otherwise it will default to the value 600ms.
Recompilation should work just fine with `make`. the source and header files are set as dependencies for the build process.

To clean up, enter `make clean`.

### Notes
For this project, Ants are represented by the **asterisk** symbol `*`, and DoodleBugs are represented by the **asperand** symbol `@`. 