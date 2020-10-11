/*************************************************************    
 * Program Filename: movie.h
 * Author: YanYan Lee
 * Date: 10/10/2020
 * Description: h file that contains movie structs and libraries
 * 		for main.c file
 * Input: None
 * Output : None
 * **************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct for movies
struct movie{
        char    *title;
        int     year;
        char    **lang;
        float   rating;
        struct  movie  *next;
};


