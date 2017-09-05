#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define ROWS 7
#define COLS 8

using namespace std;

/*
Author: Ammar Subei
Date: October 5, 2015
Connect Four Game 2.0
Two players X and O alternate placing pieces in a column. The pieces
slide down the column until another piece is reached or the bottom of 
game board is reached.
 
Assumption is Board[0][0] is top left corner of game board
top row is thus Board[0][0..COLS-1]
bottom row is [ROWS-7][0..COLS-1]
*/

// MY ADDED FUNCTIONS

typedef struct CELL *STACK;
struct CELL {
	STACK next;
	int colNum;
};

/*
function printList
input:		a pointer that points to the head of the desired stack
behavior:	it prints out the stack starting from the head
			IT'S FOR TESTING ONLY! NOT USED IN CODE!
returns:	nothing
*/

void printList(STACK head){
	while (head != NULL)
	{
		printf("%d ",head->colNum);

		head = head->next;
		
	}
	printf("\n");
}


/*
function recordMove
input:		a pointer that points to the desired stack
			input that represents the user input column
behavior:	it stacks the linked list with elements that contain the input
			to basically record the user input
returns:	it returns the pointer to the stack
*/
STACK recordMove (STACK inputStack, int input){
	// create temp pointer
	STACK tmpptr = (STACK)malloc(sizeof(struct CELL));	
	tmpptr->next = NULL;
	tmpptr->colNum = input;
	// insert new element at the head of the list
	// creating a stacked linked-list
	if(inputStack)
		tmpptr->next = inputStack;
	inputStack = tmpptr;

	return inputStack;
}

/*
function isEmpty
input:		a pointer that points to the desired stack
behavior:	checks if the stack is empty
returns:	false: if stack is not empty
			true: if stack is empty
*/
bool isEmpty(STACK inputStack){
	return (inputStack == NULL);
}

/*
function popFirstElement
input:		a pointer that points to the stack you want to pop from
			a pointer that points to the stack you want to pop onto
behavior:	it pops the first element from one stack onto another
returns:	false: if stack is empty and cannot pop from it
			true: if operation is successful
*/
bool popFirstElement(STACK *from, STACK *onto){
	// if stack is empty, operation is invalid
	if(isEmpty(*from)){
		cout << "Invalid move, please enter a valid column" << endl;
		return false;
	}
	// create temp pointer
	STACK tmpptr = (STACK)malloc(sizeof(struct CELL));
	tmpptr->next = NULL;

	// pop from one stack onto the other
	tmpptr = *onto;
	*onto = *from;
	*from = (*from)->next;
	(*onto)->next = tmpptr;
	return true;
}

/*
function deleteStack
input:		a pointer that points to the head of the desired stack
behavior:	deletes the entire stack by freeing the memory from the heap
returns:	nothing
*/
void deleteStack(STACK *inputStack){
	// if the stack pointer points to something, free its memory
	while((*inputStack) != NULL){
		STACK tmpptr = (STACK)malloc(sizeof(struct CELL));
		tmpptr = *inputStack;
		*inputStack = (*inputStack)->next;
		free(tmpptr);
	}
}

/*
function removePiece
input:		inputStack pointer to the specified stack that contains the column
			of the piece that needs to be removed
			char_ptr points to the beginning of the game board
behavior:	removes the topmost piece found in the column chosen
returns:	false: if unsuccessful
			true: if successful
*/

bool removePiece(STACK *inputStack, char *char_ptr){
	// checks if empty
	if(isEmpty(*inputStack))
		return false;

	char *addressOfPiece;
	addressOfPiece = ((*inputStack)->colNum - 1) + char_ptr;

	// go down the column if no piece is found
	while (*addressOfPiece == '-')
		addressOfPiece += COLS;
	// now remove the topmost piece in the column
	*addressOfPiece = '-';
	return true;
}

// END OF MY ADDED FUNCTIONS

/*
function initBoard
input: a pointer that is the beginning of the ROWS x COLS gameboard
behavior: the game board is initialized to all -'s
return value: none
*/
void initBoard(char *char_ptr) {

int i,j;
for (i=0;i<ROWS;i++)
    for (j=0;j<COLS;j++){
    	*char_ptr = '-';
    	char_ptr++;
    }
}

/*
function printBoard
input: char_ptr is a pointer to the beginning of the ROWS x COLS gameboard
behavior: the game board is printed to stdout with the rows labeled
return value: none
*/

void printBoard(char *char_ptr) {

	int i,j;
	for (i=1;i<=COLS;i++)
		printf("%d  ",i);

	printf("\n");
	for (i=0;i<ROWS;i++){
	    for (j=0;j<COLS;j++){
	    	printf("%c  ",*char_ptr);
	    	char_ptr++;
	    }
	    printf("\n");
	}
}
/*
function placePiece
input: 	player holds token for a player 'X' or 'O'
		columnChosen specifies the column to try and place the piece
		char_ptr is a pointer to the beginning of the ROWS x COLS gameboard
behavior: placePiece determines the address of where to store the 
		players piece, and also makes sure a valid column is chosen, 
		and that a player does not add more than ROW items in a column
return value: 	0 - something bad happened
				1 - valid column was chosen and piece was placed
		*/
		
bool placePiece(char player, int columnChosen, char *char_ptr){
	char *potentialAddressOfPiece;
	// check if the columnChosen is full
	potentialAddressOfPiece = (columnChosen - 1) + char_ptr;
	if (*potentialAddressOfPiece != '-') {
		printf("Column chosen is already full, please enter a valid column\n");
		return false;
	}

	else {
		potentialAddressOfPiece += COLS * (ROWS - 1);
		// find row to place piece.
		while (*potentialAddressOfPiece != '-')
			potentialAddressOfPiece -= COLS;

		// we are at first non -, make it player
		*potentialAddressOfPiece = player;	 
	}
	return true;
}

/*
function checkWinner
input: 	player holds token for current player 'X' or 'O'
		char_ptr is a pointer to the beginning of the ROWS x COLS gameboard
behavior: checkWinner determines if current players last move caused them to win
		code looks for four in a row, column and both diagonals
return value: 	false: game over, either a player one or board is full
				true: no winner found
		*/

bool checkWinner(char player, char *char_ptr) {
	char *placePiece;
	int i,j;
	int boardNotFull = 0; // asssume board is full, if one empty will become 1
	
	// two cases, either player put a piece in and got 4 in a row, 
	// or board is full..
	
	// we check if board is full first by checking if top row of board has open spots
	// if top row full print out message saying draw game and return 0;
	placePiece = char_ptr;
	for (i=0;i<COLS;i++) {
		boardNotFull |= (*placePiece == '-');
		placePiece++;
		} // boardNotFull will equal 1 if any column has open places
    if (boardNotFull == 0)	{
    	printf("Board Full, Draw Game\n");
    	return false;
    } else {
    	//need to look for 4 in a row of player..
    	// check for 4 in a row first. Need to check first COLS-3 
    	placePiece = char_ptr;
    	for (i=0;i<ROWS;i++){
    		for (j=0;j<(COLS-3);j++){
    			if ((player == *placePiece) && (player == *(placePiece+1)) && (player == *(placePiece+2)) &&(player== *(placePiece+3))){
    				printBoard(char_ptr);
					printf("player %c wins\n",player);
					return false;
					}
				placePiece++;
    		}
    		placePiece+=(COLS-5);
    	}
    
    	// have to check rows 0 to ROWS-3
  		placePiece = char_ptr;
    	for (i=0;i<(ROWS-3);i++){
    		for (j=0;j<COLS;j++){
    			if ((player == *placePiece) && (player == *(placePiece+COLS)) && (player == *(placePiece+COLS*2)) &&(player== *(placePiece+COLS*3))){
    				printBoard(char_ptr);
					printf("player %c wins\n",player);
					return false;
					}
				placePiece++;
    		}
    	}
    	// have to check rows 0 to COLS-3
    	// and cols 0 to COLS-3 for a diagonal towards lower right
  		placePiece = char_ptr;
    	for (i=0;i<(ROWS-3);i++){
    		for (j=0;j<(COLS-3);j++){
    			if ((player == *placePiece) && (player == *(placePiece+COLS+1)) && (player == *(placePiece+COLS*2+2)) &&(player== *(placePiece+COLS*3+3))){
    				printBoard(char_ptr);
					printf("player %c wins\n",player);
					return false;
					}
				placePiece++;
    		}
    		placePiece+=(COLS-5);
    	}    
	
	
    	// have to check rows 3 to ROWS
    	// and cols 0 to COLS-3 for a diagonal towards upper right
  		placePiece = char_ptr+3*COLS;
    	for (i=3;i<(ROWS);i++){
    		for (j=0;j<(COLS-3);j++){
    			if ((player == *placePiece) && (player == *(placePiece-COLS+1)) && (player == *(placePiece-COLS*2+2)) &&(player== *(placePiece-COLS*3+3))){
    				printBoard(char_ptr);
					printf("player %c wins\n",player);
					return false;
					}
				placePiece++;
    		}
    		placePiece+=(COLS-5);
    	}
	}// end else   	
	return true;
}

int main()
{
	// variable initializations
	bool switchPlayer 	= false;
	bool reset 			= false;
	bool notDone 		= true;
	bool validPlay		= true;
	STACK entryStack	= NULL;
	STACK undoStack		= NULL;

	char Board[ROWS][COLS]; 
	char player = 'O';
	printf("Welcome to connect four\n");
	printf("Object is to be the first person to get 4 of their tokens\n");
	printf("contiguous in a column, row, or on a diagonal, in the game board\n\n");
	printf("no wrapping is allowed\n");
	
	initBoard(&Board[0][0]);
	
	do {
		printBoard(&Board[0][0]);
		printf("Player %c pick a column:",player);

		do {
			char userInput;
			int columnChosen = 0;

			// read the first character, and ignore the rest
			cin >> userInput;
			cin.ignore(100, '\n');

			if(userInput == 'b')
				columnChosen = -1;
			else if(userInput == 'f')
				columnChosen = -2;
			else if(userInput >= '1' && userInput <= '8')
				columnChosen = atoi(&userInput);

			// if input is between 1 and 8
			if(columnChosen >= 1 && columnChosen <= 8){
				//if not reset, delete the undo stack to reset
				if(reset == false)
					deleteStack(&undoStack);

				// record the move and place the piece of player, then switch player
				entryStack = recordMove(entryStack,columnChosen);
				validPlay = placePiece(player,(entryStack->colNum),&Board[0][0]);
				reset = true;
				switchPlayer = true;
			}

			// if input was b
			else if(columnChosen == -1){
				// do not reset, and pop from entryStack onto the undoStack
				// then remove the piece from the column number in the undoStack
				reset = false;
				switchPlayer = popFirstElement(&entryStack,&undoStack);
				validPlay = removePiece(&undoStack,&Board[0][0]);
			}

			// if input was f
			else if(columnChosen == -2){
				// if not reset, pop from undoStack onto the entryStack
				// then place the piece into the column in the entryStack
				if(reset == false){
					if(switchPlayer = popFirstElement(&undoStack, &entryStack))
						validPlay = placePiece(player,(entryStack->colNum),&Board[0][0]);
				}

				// if reset is true, then there are no future moves
				else{
					cout << "Invalid move, please enter a valid column" << endl;
					validPlay = 0;
				}
			}

			// otherwise, input was invalid
			else
				cout << "Invalid move, please enter a valid column" << endl;
			
		} while (!validPlay);

		notDone = checkWinner(player,&Board[0][0]);

		// if it's time to switch player, switch player
		if(switchPlayer == true){
			if (player == 'O')
				player = 'X';
			else
				player = 'O';
		}
		printList(entryStack);
		printList(undoStack);
	} while (notDone);
}