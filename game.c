/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Damon Toumbourou
* Student Number   : s3019592
* Course Code      : BP094
* Program Code     : COSC1076
* Start up code provided by Paul Miller
* File:     game.c
***********************************************************************/ 
#include "game.h"


/* @param current the current player who has just completed their turn
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


/* @param human a pointer to details about the human player
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

 
/* @param board the gameboard to test for a winner
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

