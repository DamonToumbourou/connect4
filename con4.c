/*********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Damon Toumbourou
* Student Number   : s3019592
* Course Code      : BP094 
* Program Code     : COSC1076
* Start up code provided by Paul Miller
* File: con4.c
***********************************************************************/
#include "con4.h"


int main(void)
{
    int result;
    int min, max;
    int int_length = 1;  
    
    /* declare scoreboard for keeping track of winners */
    scoreboard scores;
   
    /* declare the two players and a pointer to who won the last game */
    struct player human_player, computer_player, *winner;

    /* initialise the scoreboard */
    init_scoreboard(scores);

    /*display menu and get menu choice until the user chooses to quit */
    
    while(TRUE) {
        printf("\nWelcome to connect 4"          );
        printf("\n--------------------"          );
        printf("\n1. Play Game"                  );
        printf("\n2. Display High Scores"        );
        printf("\n3. Quit"                       );
        printf("\n Please Enter Your Choice:\n\n");
        
        min = 1, max = 3;
        get_integer(&result, int_length, min, max);  
        printf("\nYour selection was: %d\n", result);
        
        switch(result)
        {   
            case 1:
                printf("Play Game");         

                /* initialize human player located in player.c */
                get_human_player(&human_player);
                printf("\nHuman Color: %d\n", human_player.thiscolor);
               
                /* initialize computer */
                get_computer_player(&computer_player);
                
                /* sets the color of computer after human is set to random */ 
                if (human_player.thiscolor == C_WHITE) {
                    computer_player.thiscolor = C_RED; 
                } else (computer_player.thiscolor = C_WHITE);
          
                /* play game and save return state which is the winning player*/
                winner = play_game(&human_player, &computer_player);
               
                /* add the winner to scoreboard */
                add_to_scoreboard(scores, winner);
                
                break;
                
            case 2:
                printf("\n*** SCOREBOARD ***\n");
                                
                display_scores(scores);

                break;

            case 3:
                printf("\nThanks for playing...\n");
                return EXIT_SUCCESS;
        }

    }

    return EXIT_SUCCESS;
}
