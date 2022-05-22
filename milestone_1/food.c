/*food.c -------
*
* Filename: food.c
* Description:
* Author: Manisha Suresh Kumar
* Maintainer: Kent Ong
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
*
*
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


//Create new food
Food* create_food(int x, int y, enum Type type){
    Food* new_food = malloc(sizeof(Food));

    new_food->x = x;
    new_food->y = y;
    int random = rand() % 2;
    if (type == Increase){

        if ( random == 0)
            new_food->type = 'O';
        else
            new_food ->type = '+';
    }
    else {
        if (random == 0)
            new_food->type = 'X';
        else
            new_food->type = '-';
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
    Food* foodType = foods;
    while (foodType)
    {
        if ( foodType -> x == x & foodType -> y == y)
        {
            if(foodType->type == '+' || foodType->type == 'O')
                return Increase;
            else
                return Decrease;
        }
        foodType = foodType -> next;
    }
}

Food* remove_eaten_food(Food* foods, int x, int y) {
    //Implement the code to remove food at position (x,y).
    //Create a new linked list of type Food containing only the
    //needed food and return this new list

    if(foods -> x == x && foods -> y == y)
    {
        return foods->next;
    }

    Food *newFoods = foods;
    while (newFoods->next != NULL) {
        if (newFoods->next->x == x && newFoods->next->y == y) {
            newFoods->next = newFoods->next->next;
        }
        newFoods = newFoods->next;
    }

    return foods;
}

// Display all the food
void draw_food (Food *foods)
{   Food* temp = foods;
    while(temp) {
        mvprintw(temp->y, temp->x, "%c", temp->type);
        temp = temp->next;
    }
}