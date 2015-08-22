/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Damon Toumbourou
* Student Number   : s3019592
* Course Code      : COSC1076
* Program Code     : BP064
* Start up code provided by Paul Miller
* File: board.c
 ***********************************************************************/
#include "board.h"
#include "player.h"

/**
 * @file board.c contains implementations of functions related to the game 
 * board.
 **/

/**
 * @param board the board to reset the contents of
 **/
void initialise_board(enum cell_contents board[][BOARDWIDTH])
{   
    int i, j;
    for (i = 0; i < BOARDHEIGHT; i++) {
        for (j = 0; j < BOARDWIDTH; j++) {
        board[i][j] = C_EMPTY;  
        }
    }
}
/**
 * In this requirement you are required to display the game board. 
 * The game board should be displayed as shown on the first page of the 
 * assignment specification. 
 * @param board the board to display
 **/
void display_board(enum cell_contents board[][BOARDWIDTH])
{   
    int k;
    int i;
    int j;

    printf("\n%s\n", "Current state of board is:");
    
    for (k = 1; k < BOARDWIDTH + 1; ++k) {
        printf(" %d |", k);  
    }
    for (i = 0; i < BOARDHEIGHT; ++i) {
       printf("\n----------------------------\n");
       for (j = 0; j < BOARDWIDTH; ++j) {
       
            switch(board[i][j])
            {
            case C_EMPTY:
                 printf("   |");  
                break;
            case C_WHITE:
                 printf(" %s |", WHITE_TOKEN);
                break; 
            case C_RED:
                 printf(" %s |", RED_TOKEN);
                 break;
            }
        }
    }
    printf("\n----------------------------\n");
}

