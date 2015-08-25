/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Damon Toumbourou
* Student Number   : s3019592
* Course Code      : 
* Program Code     : 
* Start up code provided by Paul Miller
***********************************************************************/
#include "scoreboard.h"

/**
 * @param board the scoreboard to initialise
 **/
void init_scoreboard(scoreboard board)
{
    int i; 
    
    for (i = 0; i < SCOREBOARDSIZE; ++i) {
        board[i].counters = 0; 
        strcpy(board[i].name, " "); 
    }
}


 /* @param board the scoreboard to display
 **/
void display_scores(const scoreboard board)
{   
    int i;

    printf("\n%s%s", "Player              | "
                   , "Score                 ");

    printf("\n%s%s", "----------------------"
                   , "----------------------");
        
    for (i = 0; i < SCOREBOARDSIZE; ++i) {
    
        printf("\n%s%22d", board[i].name, board[i].counters);  
    }
}


 /* @param board the scoreboard to add the score to @param sc the score
 * to add to the scoreboard
 */ 
BOOLEAN add_to_scoreboard(scoreboard board, const score * sc) 
{
    int i;
    int j;
    int temp_score;
    int score_to_add;

    char temp_string[22];
    char *temp;
    temp = temp_string;

    score_to_add  = sc->counters; 

    printf("\n%s%s", "Winner: ", sc->name);      
    printf("\n%s%d\n", "Score: ", sc->counters); 
    
    board[10].counters = score_to_add;
    strcpy(board[10].name, sc->name); 

    /* loop through scoreboard and will swap position if score greater 
     * starting at position 10.
     */
    i = SCOREBOARDSIZE;
    for (j = SCOREBOARDSIZE-1; j >= 0; --j) {
           
        if (board[i].counters > board[j].counters) {
            
            temp_score = board[j].counters; 
            board[j].counters = board[i].counters; 
            board[i].counters = temp_score;
           
            strcpy(temp, board[j].name);
            strcpy(board[j].name, board[i].name);
            strcpy(board[i].name, temp);

            i--;       
        }
    }

    return FALSE; 
}
