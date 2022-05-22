/*food.c -------
*
* Filename: food.c
* Description:
* Author: Manisha Suresh Kumar
* Maintainer: Gabriel Jude
* Created: Sat Sep 12 13:16:12 2020
* Last-Updated: September 12 16:51 2020
*	  By: Manisha Suresh Kumar
*
*/

/* Commentary:
*
*
*
*/

/* Change log:
*  4/26 added food symbols and required functionality
*  4/27 fixed remove food
*/

/*Copyright (c) 2016 The Trustees of Indiana University and
* Indiana University Research and Technology Corporation.
*
* All rights reserved.
*
* Additional copyrights may follow
*/

#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include "food.h"
#include <time.h>


//Create new food
Food* create_food(int x, int y, enum Type type){
    Food* new_food = malloc(sizeof(Food));
    new_food->x = x;
    new_food->y = y;
    if (type == Increase){
        new_food->type = (rand() > RAND_MAX/2) ? 'O' : '+'; //randomly decide symbol
    }
    else if(type == Decrease){
        new_food->type = (rand() > RAND_MAX/2) ? 'X' : '-'; //ditto
    }

    else
    {
        new_food->type = '=';

    }
    new_food->next = NULL;

    return new_food;
}

//Check if food exists at coordinates
bool food_exists(Food* foods, int x, int y){
    Food* temp = foods;
    while(temp){
        if(temp->x == x && temp->y == y)
            return true;
        temp = temp->next;
    }
    return false;
}



//Add new food to end of food list
void add_new_food(Food* foods, Food* new_food){
    Food* temp = foods;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = new_food;
}


enum Type food_type(Food* foods, int x, int y){
    //Implement the code to return the type of the food 
    //present at position (x, y)	
    Food* temp = foods;
    while(temp){
        if(temp->x == x && temp->y == y)
        {
            if(temp->type == '+' || temp->type == 'O')
                return Increase;
            if(temp->type == '-' || temp->type == 'X')
                return Decrease;
            if (temp->type == '=')
                return Obstacle;
        }
        temp = temp->next;
    }	
}
Food* remove_eaten_food(Food* foods, int x, int y){
	//Implement the code to remove food at position (x,y).
	//Create a new linked list of type Food containing only the
	//needed food and return this new list

	// if first element is to be removed
    if(foods -> x == x && foods -> y == y)
    {
	    return foods->next;
    }
    Food* temp = foods;
    // for all cases apart from head and end of tail
    while(temp -> next != NULL)
    {
        if(temp -> next -> x == x && temp -> next-> y == y)
        {
	        temp -> next = temp -> next -> next;
	        break;
        }

        temp = temp -> next;
    }

    return foods;
}

// Display all the food
void draw_food (Food *foods)
{   Food* temp = foods;
    while(temp) {
        //plus food are yellow, minus food are blue, obstacles are cyan
        mvprintw(temp->y, temp->x, "%c", temp->type);
        temp = temp->next;
    }
}
