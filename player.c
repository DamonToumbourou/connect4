/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Course Code      : EDIT HERE
* Program Code     : EDIT HERE
* Start up code provided by Paul Miller
* File:     player.c
***********************************************************************/
#include "player.h"
/**
 * @param human the human player to initialise
 **/


enum input_result get_human_player(struct player* human)
{
    /* placeholder return value. You should prompt the user 
     * for their name and then initialise all other values in the
     * player struct to sensible values.
     */

    /* Set players name */
    char temp_name[NAMELEN+1];

    printf("\nPlease enter your name: ");
    get_string(temp_name, NAMELEN+1);
    strcpy(human->name, temp_name);  

    printf("\nHello %s\n", human->name);

    /* set human player color using random function: 
     * if human is white goes first 
     * else computer is white.
     * */
    human->thiscolor = get_random(1, 2); 
    
    /* set piece counter to 0 */
    human->counters = 0; 
    
    /* set player type Human or Computer */
    human->type = HUMAN;

    return FAILURE;
}


/**
 * @param computer the computer player to initialise
 **/
enum input_result get_computer_player(struct player * computer)
{
    /* initialise all variables that are part of the struct to sensible 
     * values */
    
    /* set name */
    strcpy(computer->name, "Computer");

    /* set color */
    /* !!! need to set to oppisite of human player */    
    computer->thiscolor = 0; 
    
    /* set counter to zero */
    computer->counters = 0;

    /* set type of player */
    computer->type = COMPUTER;


    return FAILURE;
}

/**
 * In this requirement, you need to handle the taking of a turn - either
 * of a human or a computer player.
 *
 * For the human player, you will need to allow the user to enter the 
 * column they wish to place a token in. You will need to validate what 
 * the user enters, then place a token correctly in that column so that
 * it occupies the cell closest to the bottom of the board array for that 
 * column.
 *
 * For the computer player, you will need to randomly generate a column 
 * number to place a token in and if that column is full, generate a 
 * different column number until a column number with some free space has 
 * been found.
 L https://raw.githubusercontent.com/Homebrew/install/master/install)"
 * @param current the current player
 * @param board the game board that we will attempt to insert a token into
 * @return enum @ref input_result indicating the state of user input (in 
 * case this run involved user input
 **/


enum input_result take_turn(struct player * current,
        enum cell_contents board[][BOARDWIDTH])
{
    /*
     * Default return value - delete this comment and the return
     * value and replace it with appropriate logic to handle either
     * a human or computer turn including handling any input errors.
     */
    enum cell_contents current_token;
    int selection; 
    int length = 1;
    int i; 

    /* loop for a turn */
    if (current->type == HUMAN) {
        printf("\n%s%d\n", "Human Turn Number: "
                       , current->counters);
        
        /* get column number from human */
        printf("\n%s\n", "Please enter a column number human: "); 
        get_integer(&selection, length, MINCOLUMN, MAXCOLUMN);
            
        /* get player token color */
        current_token = current->thiscolor;

        /* add turn  counter for human */
        current->counters++;

    } else {
        printf("\n%s%d\n", "Computer Turn: "
                     , current->counters);

        /* computer column selection uses random function */
        selection = get_random(MINCOLUMN, MAXCOLUMN);
        
        /* get computer token color */
        current_token = current->thiscolor;
   
        /* increment turn counter for computer */
        current->counters++;
    }    

    /* add current player selection to the board */ 
    for (i = BOARDHEIGHT-1; i >= -1; --i) {
        /* check for full column */ 
        if (i == -1) {
            printf("Column Full!");
            take_turn(current, board);
            
        }    
        /* add token to board if slot is empty */    
        if (board[i][selection -1] == C_EMPTY) {
            board[i][selection -1] = current_token;             
            break;
        }
        
    }
    
    return FAILURE;
}

