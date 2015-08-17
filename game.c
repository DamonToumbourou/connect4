/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Damon Toumbourou
* Student Number   : s3019592
* Course Code      : 
* Program Code     : 
* Start up code provided by Paul Miller
* File:     game.c
***********************************************************************/ 
#include "game.h"

/**
 * @file game.c contains the functions that relate to the management of
 * the game.
 **/

/**
 * This requirement requires you to understand a little more about pointers.
 * We want you to understand that all pointers just point to another memory
 * address whether they are a single pointer, a pointer to a pointer, etc.
 * 
 * In this example, we want you to swap the pointers for two players. 
 * This will be called from \ref play_game with a call such as 
 * swap(&current, &other) and at the end of this function, current and
 * other's pointers will be swapped.
 * For example, if current points to the human player and other points to 
 * the computer player, at the end of this function, the player they point 
 * to will have been swapped. 
 * 
 * @param current the current player who has just completed their turn
 * @param other the next player whose turn it will be
 **/
static void swap_players(struct player ** current, struct player ** other)
{
    /* implement a classic swap using a temporary pointer */
   /*
   temporary = other;
   other  = current;
   current = temporary;
    */
}

/**
 * This is the heart of the game.
 * 
 * Firstly, you need to initialise the game by calling functions written 
 * for requirement 3. The rest of this function is then managing the game 
 * loop.
 *
 * Each player takes a turn to drop a token into a column on the game 
 * board. The task that needs to be performed will be different depending 
 * on whether this is a human or a computer player.
 *
 * Regardless of the player type, you will need to display the board as it 
 * was before the player makes their move. If the current player is a 
 * computer player, we just need to select a column at random and drop a
 * token into that column. If there is no room, try another column.
 *
 * If the current player is a human player, your program will need to ask 
 * the user what column they wish to drop a token in. This input should be 
 * validated to check that it is numeric and within the range of allowed 
 * columns.
 * 
 * Once a valid move has been entered, your program should update the 
 * gameboard. It should then check if the game has been won lost or drawn 
 * by calling and the change the current player.
 *
 * This function also checks if the game has been won, lost or drawn by 
 * calling \ref test_for_winner(), and if the game is over, returns the 
 * winner to main or NULL if the game was a draw.

 * @param human a pointer to details about the human player
 * @param computer a pointer to details about the computer player
 **/
struct player* play_game(struct player* human , struct player* computer)
{
    int selection;
    int length = 1; 
    /* declaration that allocates the board for the game */
    enum cell_contents board[BOARDHEIGHT][BOARDWIDTH];
    
    initialise_board(board);
    display_board(board);     
    
    enum playertype current;
    enum cell_contents current_token = C_WHITE;;

    if (human->thiscolor == C_WHITE) {
        current = HUMAN;    

        printf("\n%s\n", "Human goes first");
    } else { 
        current = COMPUTER;

        printf("\n%s\n", "Computer goes first");
    }

    while (TRUE) {
        if (current == HUMAN) {
            printf("\n%s\n", "Human turn:");
            printf("\n%s\n", "Please enter a column number: ");
           
            get_integer(&selection, length, MINCOLUMN, MAXCOLUMN);
            current = COMPUTER;
            current_token = human->thiscolor; 

        } else {
            printf("\n%s\n", "Computer turn:");
            
            selection = get_random(MINCOLUMN, MAXCOLUMN);
            current = HUMAN;
            current_token = computer->thiscolor; 
        }

        /*board height */
        for (int i = BOARDHEIGHT-1; i >= 0; --i) {
            if (board[i][selection -1] == C_EMPTY) {
                board[i][selection -1] = current_token;
                break;
            } 
        } 

        display_board(board);

        test_for_winner(board);     
    
    }    
      
    
    return NULL;
}

/**
 * In this requirement you are required to test what the game's current 
 * state is.
 * Possible game states are defined by the game_state enumeration:
 * enum game_state
 * {
 *    G_NO_WINNER=-1,
 *    G_DRAW,
 *    G_RED,
 *    G_WHITE
 * };
 *
 * Most of these states should be self-explanatory but let's go through 
 * their meaning.
 * 
 *    &bull; G_NO_WINNER: the game is still in progress and therefore there
 *    is no winner yet.
 * 
 *    &bull; G_DRAW: neither player has won the game but there are no more 
 *    spaces left for a player to make a move.
 *    
 *    &bull; G_RED / G_WHITE: the player whose token is the specified 
 *    colour has won the game.
 *
 * Your task in this function is to iterate over the 2-dimensional array 
 * (the board) looking for four in a row in any direction – if you find 
 * this, return the appropriate value of either G_RED or G_WHITE.
 *
 * Next, test for a draw. If none of these cases hold, return G_NO_WINNER.
 * @param board the gameboard to test for a winner
 **/
enum game_state test_for_winner( enum cell_contents board[][BOARDWIDTH])
{
    int white_count = 0;
    int red_count = 0;
    int i = 0;
    int j = 0;

    /* test for winner in a row (horizontal) */
    for (i = 0; i < BOARDHEIGHT; ++i) { 

        for (j = 0; j < BOARDWIDTH; ++j) {
      
            if (board[i][j] == C_RED) {
                red_count++;
                if (red_count >= 4) {
                    printf("\n%s\n", "Red Wins");
                }
            } else { 
                red_count = 0;    
            }

            if (board[i][j] == C_WHITE) {
                white_count++;
                if (white_count >= 4) {
                    printf("\n%s\n", "White Wins");
                }
            } else { 
                white_count = 0;
            }
        } 
    }
    
    /* test for winner in a columni (vertical) */
    for (i = 0; i < BOARDWIDTH; ++i) {

        for (j = 0; j < BOARDHEIGHT; ++j) {
        
            if (board[j][i] == C_RED) {
               red_count ++;
               if (red_count >= 4) {
                  printf("\n%s\n", "Red Wins!");
               }
            } else {
               red_count = 0;
            }

            if (board[j][i] == C_WHITE) {
                white_count++;
                if (white_count >= 4) {
                    printf("\n%s\n", "White Wins!");
                }
            } else {
                white_count = 0;
            }
        }
    }

    /* test for winner in diagnol */
    
}












