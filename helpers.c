/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Damon Toumbourou
* Student Number   : s3019592
* Course Code      : BP094
* Program Code     : COSC1076
* Start up code provided by Paul Miller
* File:     helper.c
***********************************************************************/
#include "helpers.h"

#define INPUT_LENGTH 11
#define PROMPT_LENGTH 80
#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
#define TEMP_STRING_LENGTH 11


/**
 * Deals with buffering
 **/
void read_rest_of_line(void)
{
    int ch;
    while(ch = getc(stdin), ch!=EOF && ch != '\n')
        ; /* gobble each character */
    /* reset the error status of the stream */
    clearerr(stdin);
}


/* Handles input of type integer  */
/* Taken from Steven Burrows */
int get_integer(int* integer, int length, int min, int max)
{
   int finished = FALSE;
   char tempString[TEMP_STRING_LENGTH + 2];
   int tempInteger = 0;
   char* endPtr;

   /* Continue to interact with the user until the input is valid. */
   do
   {
      
      /* Accept input. "+2" is for the \n and \0 characters. */
      fgets(tempString, length + 2, stdin);

      /* A string that doesn't have a newline character is too long. */
      if (tempString[strlen(tempString) - 1] != '\n')
      {
         printf("Input was too long.\n");
         read_rest_of_line();
      }
      else
      {
         /* Overwrite the \n character with \0. */
         tempString[strlen(tempString) - 1] = '\0';

         /* Convert string to an integer. */
         tempInteger = (int) strtol(tempString, &endPtr, 10);

         /* Validate integer result. */
         if (strcmp(endPtr, "") != 0)
         {
            printf("Input was not numeric.\n");
         }
         else if (tempInteger < min || tempInteger > max)
         {
            printf("Input was not within range %d - %d.\n", min, max);
         }
         else
         {
            finished = TRUE;
         }
      }
   } while (finished == FALSE);

   /* Make the result integer available to calling function. */
   *integer = tempInteger;

   return SUCCESS;
}


/* getString function taken from: Steven Burrows */
/* Validates string input from user */
int get_string(char* string, unsigned length)
{
   int finished = FALSE;
   char tempString[TEMP_STRING_LENGTH + 2];

   /* Continue to interact with the user until the input is valid. */
   do
   {
      /* Accept input. "+2" is for the \n and \0 characters. */
      fgets(tempString, length + 2, stdin);

      /* A string that doesn't have a newline character is too long. */
      if (tempString[strlen(tempString) - 1] != '\n')
      {
         printf("Input was too long.\n");
         read_rest_of_line();
      }
      else
      {
         finished = TRUE;
      }

   } while (finished == FALSE);

   /* Overwrite the \n character with \0. */
   tempString[strlen(tempString) - 1] = '\0';
   
   /* Make the result string available to calling function. */
   strcpy(string, tempString);

   return SUCCESS;
}

/* random numbers between 2 ints */
int get_random(int min, int max) {
    int random;
    
    srand(time(NULL));
    random = (rand() %10  + 1) % (max - min + 1) + min;
    printf("\n%d\n", random);
    return random;  
}

void waitFor (unsigned int secs) {
    int retTime = time(0) + secs;
    while (time(0) < retTime);
}


