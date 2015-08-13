/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Damon Toumbourou
* Student Number   : s3019592
* Course Code      : 
* Program Code     : 
* Start up code provided by Paul Miller
* File: con4.c
***********************************************************************/
#include "con4.h"

/**
 * @mainpage COSC1076 - Assignment 1 documentation.
 *
 * This is the main html documentation of assignment 1 for COSC1076 -
 * Advanced Programming Techniques for semester 2, 2015. You will find
 * here a description of the functions that you need to implement for
 * your assignment.
 *
 * Please note that this should not be your first stop when starting
 * your assignment. Please read the assignment 1 specifications that
 * are available on blackboard before reading this documentation. The
 * purpose of this documentation is to clarify the actual individual
 * requirements.
 *
 * This site presents you with the documentation for each function
 * that you need to implement broken down by the file that they exist
 * in. Please go to the <b>Files</b> tab and click on the file you wish to
 * get more information about and then click on that file. An
 * explanation of each function implemented in that file will be
 * displayed.
 **/

/**
 * @file con4.c contains the main function which is the entry point into the 
 * application and manages the main memory.
 **/

/**
 * the entry point into the game. You should display the main menu and 
 * respond to user requests.
 *
 * The main menu should look like this: 
 * Welcome to connect 4
 *  \n\--------------------
 * 1. Play Game
 * 2. Display High Scores
 * 3. Quit
 * Please enter your choice:
 *
 * This menu should also be redisplayed when the program returns from 
 * running an option.
 **/
int main(void)
{
    int result;
    int length = 1;  
    /* the scoreboard for keeping track of winners */
    scoreboard scores;
    /* the two players and a pointer to who won the last game */
    struct player human_player, computer_player, *winner;

    /* with each of the comments below, insert the code that performs 
     * this function 
     */

    /* initialise the scoreboard */
     
    /*display menu and get menu choice until the user chooses to quit */
    printf("\nWelcome to connect 4"          );
    printf("\n--------------------"          );
    printf("\n1. Play Game"                  );
    printf("\n2. Display High Scores"        );
    printf("\n3. Quit"                       );
    printf("\n Please Enter Your Choice:\n\n");
    
    int min = 1, max = 3;
    get_integer(&result, length, min, max);  
    printf("\nYour selection was: %d\n", result);
    
    switch(result)
    {   
        case 1:
            printf("Play Game");         

            /* initialize human and computer player located in player.c */
            get_human_player(&human_player);
            printf("\nHuman Color: %d\n", human_player.thiscolor);
           
            /* set computer color */ 
            get_computer_player(&computer_player);
             
            if (human_player.thiscolor == C_WHITE) {
                computer_player.thiscolor = C_RED; 
            } else (computer_player.thiscolor = C_WHITE);
            
                 
            printf("\ncomputer color: %d\n", computer_player.thiscolor);

            /* initialize the game board located in board.c */         
        

            /* play game */
            play_game(&human_player, &computer_player);
           
            break;

        case 2:
            printf("Display High Scores");
            break;

        case 3:
            printf("\nThanks for playing...\n");
            return EXIT_SUCCESS;
    }

		    /* if there was not a draw, add player to the scoreboard in 
		     * order by number of tokens in play
		     */

		    /* let the user know who won */

		    /* if there was a draw, alert the user to this fact */

		/* display the scoreboard option */

		/* quit the program option */
    return EXIT_SUCCESS;

}
