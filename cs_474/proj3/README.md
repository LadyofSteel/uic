# CS 474 Project 3

### Info
Using **C++11**, this project is for managing household appliances held for sale in a website.

### Usage
A makefile is provided for easier compilation. Enter `make` or `make proj3` to build the project. Enter `make run` to run the executable. If you want to build and run, just enter `make all`.
Recompilation should work just fine with `make`. the source and header files are set as dependencies for the build process.

To clean up, enter `make clean`.

### Notes
Sample appliance files are included. Note that the file names start with "file" and the appliance number, and end with a `txt` extension (e.g file3.txt). Every entry for the appliance is on a separate line, and the last line contains the filepaths for the images (delimited by commas). Also note that the program does not handle exceptions and edge cases, I wrote the whole thing in a very rushed time. In addition, my commenting (and documentation style) is very inconsistent in this project, entirely due to the little time I had to get something working in this.