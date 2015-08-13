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
    printf("\n%s\n", "init board"); 
    for (int i = 0; i < BOARDHEIGHT; i++) {
        for (int j = 0; j < BOARDWIDTH; j++) {
        board[i][j] = C_EMPTY;  
        printf("\n%d\n", board[i][j]);
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
    /*
    for (int i = 1; i < 7; ++i) {
       printf(" $d | ", i); 
    }
    */
 }
 


