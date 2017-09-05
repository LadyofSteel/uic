Course: CS 201
Project #: 2
Course Instructor: Prof. Mitchell D. Theys


Student Name: Ammar Subei
Source file name: asubei2.cpp

Program Info:
Connect Four Game 2.0
Two players X and O alternate placing pieces in a column. The pieces slide down the column until another piece is reached or the bottom of 
game board is reached. Players have the ability to go back one move, or go forward one move if no other moves were added.

Methods:
Used two linked-lists, in stacked fashion, to implement the undo/redo functions. One list stacks the user input, and the other stacks 
whatever is undone (back moves). Also created functions that help implement the usage of those two stacks. Function isEmpty check if a 
stack is empty or not. Function deleteStack deletes the specified stack by freeing the memory from the heap. Function recordMove records 
a move (user input) by inserting the input column number at the head of entryStack. Function popFirstElement pops the first element from 
the specified (from) stack onto the other (onto) stack. And the last function removePiece removes the topmost piece from the user-specified 
column. 

Problems encountered:
I encountered multiple seg-faults due to my two stacks, and they were mainly occuring in very specific conditions. One of such conditions was when I wanted to go back one move right at the beginning of the game. 

Solutions:
I created the simple isEmpty function to avoid problems with initial conditions that could cause seg-faults and errors. 
I also used two extra boolean variables; one (switchPlayer) checks if it's time to switch players, and one (reset) checks if it's time 
to reset/delete the undoStack that stores the undo moves.  

Testing:
I played the game with my friends, checking all possible inputs and situations that might cause certain outcomes/bugs. I also used a 
printList function to print out the two lists/stacks that I created to store the entries and undo's, so I can visually check if my 
operations on those stacks were going well.

