/* snake.c -------
 *
 * Filename: snake.c
 * Description:
 * Author: Rishabh Agrawal
 * Maintainer: Gabriel Jude & Kent Ong
 * Created: Sun Sep 13 9:12:30 2020
 * Last-Updated: September 13 22:40 2020
 *           By: Rishabh Agrawal
 *
 */

/* Commentary:
 * 4/23 changes direction no matter what the previous direction is 
 *
 *
 */

/* Change log:
 * 4/23 added move functionality
 * 4/30 changed location of prevDir variable and commented out eatitself
 */

/* Copyright (c) 2016 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */


#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "snake.h"
#include "key.h"
#include <ncurses.h>
//static int prevDir; //keep track of previous direction


// Initialize snake
Snake* init_snake(int x, int y){
  Snake* head = create_tail(x, y);
  Snake* tail1 = create_tail(x-1, y);
  Snake* tail2 = create_tail(x-2, y);
  tail1->next = tail2;
  head->next = tail1;
  return head;
}

// Creates one tail
Snake* create_tail(int x, int y){
  Snake* snake = malloc(sizeof(snake));
  snake->color[0] = 0;
  snake->color[1] = 0;
  snake->color[2] = 255;
  /* snake->color = {0, 0, 255}; */
  snake->symbol = '#';
  snake->next = NULL;
  snake->x = x;
  snake->y = y;
  return snake;
}

bool snake_collision(Snake* first, Snake* second)
{
    Snake* temp1 = first;
    Snake* temp2 = second;
    int length1 = len(first);
    int length2 = len(second);
    int i =0, j = 0;
    for ( i = 0; i < length1; i++)
    {

        int head_1_x = temp1 -> x;
        int head_1_y = temp1 -> y;
        for ( j = 0; j < length2; j++)
        {
            int head_2_x = temp2 -> x;
            int head_2_y = temp2 -> y;
            if ( (head_1_x == head_2_x) && (head_1_y == head_2_y))
            {
                return true;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1 -> next;
        temp2 = second;
    }
    return false;
}


// Moves the snake in the input direction
Snake* move_snake(Snake* snake, int direction){
    // TODO
  Snake* new_head = malloc(sizeof(new_head));

  
  // Set the new head to have the x and y coordinates as the existing head of the snake
  new_head->x = snake->x;
  new_head->y = snake->y;

  // implemented new code below to change movement

  switch(direction) {
    case UP:

    //Write code to make the new head go up by 1 cell

	if (prevDir == DOWN)
    {
        new_head->y = new_head->y + 1;
	    prevDir = DOWN;
    }
	else
    {
        new_head -> y = new_head -> y - 1;
	    prevDir = direction;
    }
	break;

    case DOWN:
    //Write code to make the new head go down by 1 cell
    if (prevDir == UP)
    {
        new_head -> y = new_head -> y - 1;
        prevDir = UP;
    }
    else
    {
        new_head->y = new_head->y + 1;
        prevDir = direction;
    }
	break;

    case RIGHT:
    //Write code to make the new head go right by 1 cell

	if(prevDir == LEFT)
    {
        new_head->x = new_head->x - 1;
	    prevDir = LEFT;
    }
	else
    {
        new_head->x = new_head->x + 1;
	    prevDir = direction;
    }
	break;

    case LEFT:
    //Write code to make the new head go left by 1 cell

	if (prevDir == RIGHT)
    {
        new_head->x = new_head->x + 1;
	    prevDir = RIGHT;
    }
	else
    {
        new_head->x = new_head->x - 1;
	    prevDir = direction;
    }
	break;
  }

  //Set new head as the new head of the entire snake
  new_head->next = snake;

  //Add all the features (color and symbol) to the new cell
  new_head->color[0] = snake -> color[0];
  new_head->color[1] = snake -> color[1];
  new_head->color[2] = snake -> color[2];
  /* snake->color = {0, 0, 255}; */
  new_head->symbol = '#';
    
  // Delete the tail from the snake: HINT - there is a remove tail function below
  remove_tail(new_head);

  return new_head;
}

Snake* move_snake2(Snake* snake, int direction) {
    Snake *new_head = malloc(sizeof(new_head));


    // Set the new head to have the x and y coordinates as the existing head of the snake
    new_head->x = snake->x;
    new_head->y = snake->y;

    // implemented new code below to change movement

    switch (direction) {
        case UP:

            //Write code to make the new head go up by 1 cell

            if (prevDir2 == DOWN) {
                new_head->y = new_head->y + 1;
                prevDir2 = DOWN;
            } else {
                new_head->y = new_head->y - 1;
                prevDir2 = direction;
            }
            break;

        case DOWN:
            //Write code to make the new head go down by 1 cell
            if (prevDir2 == UP) {
                new_head->y = new_head->y - 1;
                prevDir2 = UP;
            } else {
                new_head->y = new_head->y + 1;
                prevDir2 = direction;
            }
            break;

        case RIGHT:
            //Write code to make the new head go right by 1 cell

            if (prevDir2 == LEFT) {
                new_head->x = new_head->x - 1;
                prevDir2 = LEFT;
            } else {
                new_head->x = new_head->x + 1;
                prevDir2 = direction;
            }
            break;

        case LEFT:
            //Write code to make the new head go left by 1 cell

            if (prevDir2 == RIGHT) {
                new_head->x = new_head->x + 1;
                prevDir2 = RIGHT;
            } else {
                new_head->x = new_head->x - 1;
                prevDir2 = direction;
            }
            break;
    }
}

Snake* move_snakeE1(Snake* snake, int direction)
{
    Snake* new_head = malloc(sizeof(new_head));


    // Set the new head to have the x and y coordinates as the existing head of the snake
    new_head->x = snake->x;
    new_head->y = snake->y;

    // implemented new code below to change movement

    switch(direction) {
        case UP:

            //Write code to make the new head go up by 1 cell

            if (prevDirE1 == DOWN)
            {
                new_head->y = new_head->y + 1;
                prevDirE1 = DOWN;
            }
            else
            {
                new_head -> y = new_head -> y - 1;
                prevDirE1 = direction;
            }
            break;

        case DOWN:
            //Write code to make the new head go down by 1 cell
            if (prevDirE1 == UP)
            {
                new_head -> y = new_head -> y - 1;
                prevDirE1 = UP;
            }
            else
            {
                new_head->y = new_head->y + 1;
                prevDirE1 = direction;
            }
            break;

        case RIGHT:
            //Write code to make the new head go right by 1 cell

            if(prevDirE1 == LEFT)
            {
                new_head->x = new_head->x - 1;
                prevDirE1 = LEFT;
            }
            else
            {
                new_head->x = new_head->x + 1;
                prevDirE1 = direction;
            }
            break;

        case LEFT:
            //Write code to make the new head go left by 1 cell

            if (prevDirE1 == RIGHT)
            {
                new_head->x = new_head->x + 1;
                prevDirE1 = RIGHT;
            }
            else
            {
                new_head->x = new_head->x - 1;
                prevDirE1 = direction;
            }
            break;
    }

    //Set new head as the new head of the entire snake
    new_head->next = snake;

    //Add all the features (color and symbol) to the new cell
    new_head->color[0] = snake -> color[0];
    new_head->color[1] = snake -> color[1];
    new_head->color[2] = snake -> color[2];
    /* snake->color = {0, 0, 255}; */
    new_head->symbol = '#';

    // Delete the tail from the snake: HINT - there is a remove tail function below
    remove_tail(new_head);

    return new_head;
}

Snake* move_snakeE2(Snake* snake, int direction)
{
    Snake* new_head = malloc(sizeof(new_head));


    // Set the new head to have the x and y coordinates as the existing head of the snake
    new_head->x = snake->x;
    new_head->y = snake->y;

    // implemented new code below to change movement

    switch(direction) {
        case UP:

            //Write code to make the new head go up by 1 cell

            if (prevDirE2 == DOWN)
            {
                new_head->y = new_head->y + 1;
                prevDirE2 = DOWN;
            }
            else
            {
                new_head -> y = new_head -> y - 1;
                prevDirE2 = direction;
            }
            break;

        case DOWN:
            //Write code to make the new head go down by 1 cell
            if (prevDirE2 == UP)
            {
                new_head -> y = new_head -> y - 1;
                prevDirE2 = UP;
            }
            else
            {
                new_head->y = new_head->y + 1;
                prevDirE2 = direction;
            }
            break;

        case RIGHT:
            //Write code to make the new head go right by 1 cell

            if(prevDirE2 == LEFT)
            {
                new_head->x = new_head->x - 1;
                prevDirE2 = LEFT;
            }
            else
            {
                new_head->x = new_head->x + 1;
                prevDirE2 = direction;
            }
            break;

        case LEFT:
            //Write code to make the new head go left by 1 cell

            if (prevDirE2 == RIGHT)
            {
                new_head->x = new_head->x + 1;
                prevDirE2 = RIGHT;
            }
            else
            {
                new_head->x = new_head->x - 1;
                prevDirE2 = direction;
            }
            break;
    }

    //Set new head as the new head of the entire snake
    new_head->next = snake;

    //Add all the features (color and symbol) to the new cell
    new_head->color[0] = snake -> color[0];
    new_head->color[1] = snake -> color[1];
    new_head->color[2] = snake -> color[2];
    /* snake->color = {0, 0, 255}; */
    new_head->symbol = '#';

    // Delete the tail from the snake: HINT - there is a remove tail function below
    remove_tail(new_head);

    return new_head;
}

Snake* remove_tail(Snake* snake){
    Snake* end = snake;
    if(len(snake) >= 3)
    {
        while(end->next->next != NULL)
            end = end->next;
    }
    if ( len(snake) == 2)
    {
        end = end -> next;
    }

    if (len(snake) == 1)
    {
       end = NULL;
       return snake;
    }
    end->next = NULL;
    return snake;
}

// draws the snake on the board
void draw_snake(Snake* snake){
  while(snake){
    mvprintw(snake->y, snake->x, "%c", snake->symbol);
    snake = snake->next;
  }
}

void reverseMovement(Snake* snake, int x ,int y, int direction)
{
    Snake *prev = NULL, *current = snake, *next  = NULL;
    while ( current != NULL)
    {
        next = current -> next;
        current -> next = prev;
        prev = current;
        current = next;
    }
    snake = prev;
    while (snake != NULL)
    {
        create_tail(snake -> x, snake -> y);
        snake = snake -> next;
    }
}


// checks if it eats itself, if it does, then return true
bool eat_itself(Snake* snake)
{
    // TODO for Milestone 3 only
    int headX = snake -> x;
    int headY = snake -> y;
    Snake *body = snake -> next;
    //body includes tail
    while(body != NULL)
    {
	    if(body -> x == headX && body -> y == headY && len(snake) >= 4)
	    {
	        return true;
	    }
	    body = body -> next;
    }
    return false;
}

int len(Snake* snake)
{
    int length = 0; //changed this to 0
    while(snake)
    {
	length++;
	snake = snake -> next;
    }
    return length;
}
