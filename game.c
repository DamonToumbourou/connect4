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
    struct player *temp;

    temp = *current;
    *current = *other;
    *other = temp; 
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
struct player* play_game(struct player *human , struct player *computer)
{
    /* Function for controlling game */ 
    /* declaration that allocates the board for the game */
    enum cell_contents board[BOARDHEIGHT][BOARDWIDTH];
    enum game_state check_winner;

    /* variable for storing current player */
    struct player *current;
    struct player *other;

    /* initialize the game board */
    initialise_board(board);

    /* display the game board before turn */
    display_board(board);
    
    /* determine current player (white goes first) */ 
    if (human->thiscolor == C_WHITE) {
        current = human;
        other = computer;

        printf("\n%s\n", "Human goes first");
   
    } else { 
        current = computer;
        other = human; 
            
        printf("\n%s\n", "Computer goes first");
    }

    /* human and computer take a turn 
     * until winner found then loop exit.
     * */
    while(TRUE) {
    
        /* pointer to current player passed to take turn function */
        take_turn(current, board);
        
        /* board is displayed after turn is made to show changes */
        display_board(board);

        /* run the test for winner function and save result in variable
         * for saving latest winner state */
        check_winner = test_for_winner(board);
        
        if (check_winner == G_RED) {
            printf("\nRED CONNECTED 4!\n");
            printf("\n%s%s\n", "You win: ", current->name);              
              
            return current;

        } else if (check_winner == G_WHITE) {
            printf("\nWHITE CONNECTED 4!\n");
            printf("\n%s%s\n", "You win: "
                             , current->name);
            return current; 
        } 
        
        /* swap current players using pointer swap */
        swap_players(&current, &other);  
        
        printf("\n%s%s\n", "Current player is: "
                         , current->name );
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
 *
 * Main test for winner function controls the three functions I use to 
 * check board for winner. Function names are self explanatory. 
 * 
 * @param board the gameboard to test for a winner
 **/
enum game_state test_for_winner( enum cell_contents board[][BOARDWIDTH])
{
    enum game_state winner_test;    
    
    /* run the function to test for horizontal winner */
    winner_test = test_for_winner_horizontal(board); 

    if (winner_test != G_NO_WINNER) {
        return winner_test; 
    }
    
    /* run the function to test for vertical winner */ 
    winner_test = test_for_winner_vertical(board);

    if (winner_test != G_NO_WINNER) {
        return winner_test;
    }

    /* run the function to test for diagonal winner */
    winner_test = test_for_winner_diagonal(board);
    if (winner_test != G_NO_WINNER) {
        return winner_test;
    }

    return G_NO_WINNER; 
}


enum game_state test_for_winner_horizontal(enum cell_contents board[][BOARDWIDTH])
{   
    int i;
    int j;
    int red_count;
    int white_count;

    red_count = 0;
    white_count = 0; 

    for (i = 0; i < BOARDHEIGHT; ++i) { 
       
        for (j = 0; j < BOARDWIDTH; ++j) {
      
            if (board[i][j] == C_RED) {
                red_count++;
                if (red_count >= 4) {
                    
                    return G_RED;
                }

            } else { 
                red_count = 0;    
            }

            if (board[i][j] == C_WHITE) {
                white_count++;
                if (white_count >= 4) {
                
                    return G_WHITE; 
                }

            } else { 
                white_count = 0;
            }
        } 
    }

    return G_NO_WINNER; 
}


enum game_state test_for_winner_vertical(enum cell_contents board[][BOARDWIDTH]) 
{
    int i;
    int j;
    int red_count;
    int white_count;

    red_count = 0;
    white_count = 0;


     for (i = 0; i < BOARDWIDTH; ++i) {           
                                                   
         for (j = 0; j < BOARDHEIGHT; ++j) {
         
             if (board[j][i] == C_RED) {
                 red_count ++;
                
                 if (red_count >= 4) {
                     return G_RED;
                 }
                                                   
             } else {
                red_count = 0;
             }
                                                   
             if (board[j][i] == C_WHITE) {
                 white_count++;
             
                 if (white_count >= 4) {
                     return G_WHITE;
                 }
                                                   
             } else {
                 white_count = 0;
             }
         }
    }

    return G_NO_WINNER;
} 


enum game_state test_for_winner_diagonal(enum cell_contents board[][BOARDWIDTH])
{
    int i;
    int j;
    int k;
    int right_red_count;
    int left_red_count;
    int right_white_count;
    int left_white_count; 

    left_red_count = 0;
    right_red_count = 0;
    left_white_count = 0;
    right_white_count = 0;

    for (i = 0; i < BOARDHEIGHT; ++i) {
        
        for (j = 0; j < BOARDWIDTH; ++j) {
            
            if (board[i][j] == C_EMPTY) {
                continue;       
            }

            for (k = 0; k < 4; ++k) {

                if ((j+k < BOARDWIDTH-1) && (i+k < BOARDHEIGHT)) {
                    
                    if (board[i + k][j + k] == C_RED) {
                        right_red_count++;
                    }
    
                    if (board[i + k][j + k] == C_WHITE) {
                        right_white_count++;
                    }
                }
           
                if ((j-k >= 0) && (k+i < BOARDHEIGHT)) {   

                    if (board[i + k][j - k] == C_RED) {
                        left_red_count++;
                    }

                    if (board[i + k][j - k] == C_WHITE) {
                        left_white_count++;
                    }
                }
             }
  
            /* test red */
            if (left_red_count == 4 || right_red_count == 4) {
                return G_RED;
            } else { 
                left_red_count = 0; 
                right_red_count = 0;
            }

            /* test white */
            if (left_white_count == 4 || right_white_count == 4) {
                return G_WHITE;
            } else {
                left_white_count = 0;
                right_white_count = 0; 
            }
            
        }
    }
    
    return G_NO_WINNER;
}

