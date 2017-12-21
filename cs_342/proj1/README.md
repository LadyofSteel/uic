# CS 342 Project 1

### Info
Using **Java**, this project should implement the card game of Five Card Draw in Poker. The wikipedia page [Five Card Draw](https://en.wikipedia.org/wiki/Five-card_draw) explains the order in which cards are given to the players and Poker determines the "value" of each hand.

### Usage
A makefile is provided for easier compilation. Enter `make` or `make build` to build the project. Enter `make run` to run the program. If you want to build and run, just enter `make all`.
Recompilation should work just fine with `make`, since the source files are set as dependencies for the build process.

For any existing unit tests (using JUnit4), you can enter `make tests` to build your unit tests, and `make runtests` to run your JUnit tests. Note that you need to include the JUnit test class names in the Makefile before using this.

To clean up, enter `make clean`.

#### Notes
* The opponent player does not have the AI implemented. As of now, the CPU players are simply dealt the cards, and that's it. Their hands are compared with everyone else at the end.
* I have implemented the extra-credit card sort.