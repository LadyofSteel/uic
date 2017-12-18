# CS 342 Project 3

Due date: Thursday, Oct. 26th

Authors:

* Ammar Subei
* Daniel Kloza
* Margi Ghandi

### Usage
A makefile is provided for easier compilation. Enter `make` or `make build` to build the project. Enter `make run` to run the program. If you want to build and run, just enter `make all`.
Recompilation should work just fine with `make`, since the source files are set as dependencies for the build process.

For any existing unit tests (using JUnit4), you can enter `make tests` to build your unit tests, and `make runtests` to run your JUnit tests. Note that you need to include the JUnit test class names in the Makefile before using this.

To clean up, enter `make clean`.

### Notes
This program only implements two (out of four) solving algorithms; Single and Hidden Single algorithms. If it's possible, the program can still solve the entire puzzle using just these two algorithms. If that's not possible, then the program will fill in as much as it can using the two algorithms. Information about how to use the UI can be found in the menu bar under the `Help` menu.