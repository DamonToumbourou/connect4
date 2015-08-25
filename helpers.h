/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Damon Toumbourou
* Student Number   : s3019592
* Course Code      : BP094
* Program Code     : COSC1076
* Start up code provided by Paul Miller
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bool.h"

/**
 * @file helpers.h contains the datastructures used for various helper 
 * functioons and their function prototypes
 **/
#ifndef HELPERS_H
#define HELPERS_H
/**
 * the possible values that can be returned from custom input handling 
 * functions
 **/
enum input_result
{
    /**
     * the input was valid
     **/
    SUCCESS,
    /**
     * the input was not valld
     **/
    FAILURE,
    /**
     * the user requested to return to the menu either by pressing enter on
     * an empty line or pressing ctrl-d on an empty line
     **/
    RTM=-1
};

/**
 * call this function whenever you detect buffer overflow but only call this
 * function when this has happened.
 **/
void read_rest_of_line(void);

int get_integer(int* integer, int length, int min, int max);

int get_string(char* string, unsigned length);

int get_random(int min, int max); 
#endif

