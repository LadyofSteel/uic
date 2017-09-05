#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "solveSK.h"

//board is n by n


char ** loadBoard(const char * filePath, int *n);
void printBoard(char ** board, int n);

char base_char;

void testSolveSK(){
    int n;
    char filename[255];
    printf("Please enter file name that contains the desired unsolved Sudoku puzzle: ");
    if (scanf("%s", filename) < 0)
        printf("Error reading input file!");

    char ** board = loadBoard(filename, &n);
    printBoard(board, n);
    printf("-----------------------------------Solving sudoku-----------------------------\n");
    solveSK(board, n);
    printBoard(board, n);
    printf("------------------------------------------------------------------------------\n");
 }

int main()
{
    testSolveSK();
    return 0;
}

char ** loadBoard(const char * filePath, int *n){
    FILE *fp;
    char line[300];
    fp = fopen (filePath, "r");
    if (fp == NULL) {
        printf("file %s can not be found!!!\n Program exiting...\n", filePath);
        exit(EXIT_FAILURE);
    }
    if(fgets ( line, sizeof(line), fp ) != NULL ){
        *n = atoi(line);
    }
    printf("n= %d\n", *n);
    if(*n <= 9){
        base_char = '1';
    }else{
        base_char = 'a';
    }

    int squareN = *n * *n;
    char ** board = (char**)malloc(sizeof(char*) * squareN );
    int i, j;
    char delimiter[2] = " ";
    for(i = 0; i < squareN; i++) board[i] = (char*)malloc(sizeof(char)* squareN);
    i = 0;
    while(fgets(line, sizeof(line),fp) != NULL ) /* read a line */
    {    j = 0;
         char *token = strtok (line, delimiter);
         if(token != NULL){
            if(strcmp(token,"-") == 0) board[i][j++] = '-';
            else board[i][j++] = token[0];
         }
         while (token != NULL){
            token = strtok (NULL, delimiter);
            if(token != NULL){
                if(strcmp(token,"-") == 0) 
                    board[i][j++] = '-';
                else board[i][j++] = token[0];
            }
         }
         i++;
    }
    fclose(fp);
    return board;
}

void printBoard(char ** board, int n){
// Prints board in a nice format, as shown by the professor
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n ; j++){
            printf("%c ", board[i][j]);
            if(j == (n-1)/2)
            {
                printf("| ");
            }
        }
        printf("\n");

        if(i % 2 == 1 && i != n-1)
        {
            printf("------+------\n");
        }
    }
}
