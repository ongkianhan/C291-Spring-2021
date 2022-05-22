//Gabriel Jude Final Project 4/23/2021

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "food.h"
#include "game_window.h"
#include "key.h"
#include "game.h"
#include <string.h>
#include "maxHeap.h"

 struct save
{
    int points, lives, foodEaten;
    gamewindow_t *window;
    Snake *snake;
    Food *foods;
    maxHeap maxHeap;
};



void generate_points(int *food_x, int *food_y, int width, int height, int x_offset, int y_offset)
{
    *food_x = rand() % width + x_offset;
    *food_y = rand() % height + y_offset;
}

void game()
{
    enum State state = INIT; // Set the initial state
    static int x_max, y_max; //Max screen size variables
    static int x_offset, y_offset; // distance between the top left corner of your screen and the start of the board
    static int count = 0;
    gamewindow_t *window; // Name of the board
    Snake *snake, *snake2; // Player one and player 2
    Snake *enemy1, *enemy2; //enemy snakes
    Food *foods,*new_food; // List of foods (Not an array)
    srand(time(0));
    maxHeap heap; // init max_heap
    struct save thisGame; //init save
    FILE *fp, *fp2,*fp3;
    char filePath[100] = "./saves/";
    char fileName[50];
    char filePath2[100] = "./saves/";
    char input[50];
    char filePath3[100] = "./saves/";
    char input2[50];
    char difficulty;
    /*FILE *read;
    read = fopen("./saves/save_best_5.game", "r");
    int array[5];
    int loop, num;
    while(fread(&heap, sizeof(struct maxHeap), 1, read))
    {
        thisGame.maxHeap[0] = heap.bestScore[0];
        thisGame.maxHeap[1] = heap.bestScore[1];
        thisGame.maxHeap[2] = heap.bestScore[2];
        thisGame.maxHeap[3] = heap.bestScore[3];
        thisGame.maxHeap[4] = heap.bestScore[4];
    }
    copy_heap(thisGame.maxHeap, heap);
    fclose(read);*/ //code to implement saving to save_best_5.game


    const int height = 30; 
    const int width = 70;
    char ch;
    char prevCh = NOCHAR; //keep track of previous input
    char prevChE1 = NOCHAR, prevChE2 = NOCHAR, prevCh2 = NOCHAR; // prevCh for enemy1, enemy2 and second player
    static int points = 0; //keep track of points
    int foodEaten = 0; //keep track of food eaten
    int lives = 3;    //init lives

    struct timespec timeret, timeretEnemy1,timeretEnemy2;
    timeret.tv_sec = 0;
    timeret.tv_nsec = 999999999/4;
    timeretEnemy1.tv_sec = 0;
    timeretEnemy1.tv_nsec = 999999999/4;
    timeretEnemy2.tv_sec = 0;
    timeretEnemy2.tv_nsec = 999999999/4;

    while(state != EXIT)
    {
        switch(state)
	{
        case INIT:
            initscr();
            start_color();
            nodelay(stdscr, TRUE); //Dont wait for char
            noecho(); // Don't echo input chars
            getmaxyx(stdscr, y_max, x_max);
            keypad(stdscr, TRUE); // making keys work
            curs_set(0); // hide cursor
            timeout(100);

            // Setting height and width of the board -> this sets the start point of the board, at coordinates (x_offset, y_offset)
            x_offset = (x_max / 2) - (width / 2);
            y_offset = (y_max / 2) - (height / 2);
            
            //Init board
            window = init_GameWindow(x_offset, y_offset, width, height);


            // Init snake & enemies
            //snake is green, enemy1 is red, enemy2 is magenta, snake2 is
            //background is white

            init_pair(1,COLOR_RED, COLOR_BLACK);
            init_pair(2, COLOR_GREEN, COLOR_BLACK);
            init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
            init_pair(7, COLOR_WHITE, COLOR_BLACK);

            //all food and obstacles are cyan
            init_pair(6,COLOR_CYAN,COLOR_BLACK);

            // used to color the menu
            init_pair(3,COLOR_RED, COLOR_WHITE); //color selected option
            init_pair(4, COLOR_BLUE, COLOR_BLACK);  //color not selected options




            snake = init_snake(x_offset + (width / 2), y_offset + (height / 2));

            enemy1 = init_snake(x_offset + (width / 2) + 5, y_offset + (height / 2) + 5);

            enemy2 = init_snake(x_offset + (width / 2) - 5, y_offset + (height / 2) - 5);


            // Init foods
            int food_x, food_y, i,j,k, numFood, numObst;
            enum Type type;


            // implemented text to prompt user to select difficulty of game
            while ( (ch != 'E' || ch != 'e') || (ch != 'h' || ch != 'H') || ( ch != 'V' || ch != 'v') || (ch!= 'q' || ch != 'Q') || ( ch != 'l' || ch
            != 'L'))
            {
                ch = get_char();
                mvprintw(14,10, "Please select the difficulty of the game first, followed by multiplayer option:");
                mvprintw(15,10, "E/e for Easy, H/h for Hard, V/v for Advanced");
                mvprintw(16,10, "L/l to load a saved game");
                mvprintw(17,10, "Press q or Q to exit");
                mvprintw(18,10, "Press M or m for multiplayer, n or N for single player");
                mvprintw(20,20, "Key entered: %c", ch);

                difficulty = ch;

                // Easy = 1x speed, Hard = 2x speed, Advanced = 4x speed
                // Easy = 20 food, 5 obstacles
                // Hard = 15 food, 10 obstacles
                // Advanced = 10 food, 15 obstacles
                if ( ch == 'e' || ch == 'E')
                {
                    numFood = 20;
                    numObst = 5;
                    break;
                }

                if ( ch == 'h' || ch == 'H')
                {
                    timeret.tv_nsec *= 0.5;
                    timeretEnemy2.tv_nsec *=0.5;
                    timeretEnemy1.tv_nsec *=0.5;
                    numFood = 15;
                    numObst = 10;
                    break;
                }

                if ( ch == 'V' || ch == 'v')
                {
                    timeret.tv_nsec *= 0.25;
                    timeretEnemy2.tv_nsec *=0.25;
                    timeretEnemy1.tv_nsec *=0.25;
                    numFood = 10;
                    numObst = 15;
                    break;
                }

                if ( ch == 'Q' || ch == 'q')
                {
                    state = EXIT;
                    break;
                }

                if ( ch == 'l' || ch == 'L')
                {
                    state = LOAD;
                    break;
                }

            }

            if ( state == LOAD)
            {
                clear();
                break;
            }


            while ( (ch != 'M' || ch != 'm') || (ch != 'n' || ch != 'N') )
            {
                ch = get_char();
                mvprintw(14,10, "Please select the difficulty of the game first, followed by multiplayer option:");
                mvprintw(15,10, "E/e for Easy, H/h for Hard, V/v for Advanced");
                mvprintw(16,10, "L/l to load a saved game");
                mvprintw(17,10, "Press q or Q to exit");
                mvprintw(18,10, "Press M or m for multiplayer, n or N for single player");
                mvprintw(20,20, "Key entered: %c", ch);
                if ( ch != 'M' || ch != 'm' )
                {
                    snake2 = init_snake(x_offset + (width / 2), y_offset + (height / 2) + 10);
                    state = ALIVE;
                    break;
                }

                if ( ch != 'N' || ch != 'n' )
                {
                    break;
                }
            }


            if ( (ch == 'E' || ch == 'e') || (ch == 'h' || ch == 'H' ) || ( ch == 'V' || ch == 'v'))
            {
                state = ALIVE;
            }

            //Generate 20 foods changed to 10 to accommodate for obstacles
            generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
            type = (rand() > RAND_MAX/2) ? Increase : Decrease; // Randomly deciding type of food
            foods = create_food(food_x, food_y, type);
            for(i = 1; i < numFood; i++) //changed to 10
	        {
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                while (food_exists(foods,food_x, food_y))
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                type = (rand() > RAND_MAX/2) ? Increase : Decrease;
                new_food = create_food(food_x, food_y, type);
                add_new_food(foods, new_food);
            }
            for ( i = 0; i < numObst; i++)
            {
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                while (food_exists(foods,food_x, food_y))
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                type = Obstacle;
                new_food = create_food(food_x, food_y, type);
                new_food -> height = (rand() % 3) + 1;
                new_food -> width = (rand() % 3) + 1;
                int size = (new_food -> height > new_food -> width) ? new_food -> height : new_food -> width;
                add_new_food(foods, new_food);
                bool stopLoop = false;
                bool surroundings = false;
                if ( size > 1) //if obstacle size >= 2, we have to check if there are surrounding foods that block it.
                {
                    //check in a NxN square around the obstacle, with the obstacle being in the center
                    for ( j = -1; (j < 2) && !stopLoop; j++)
                    {
                        int xPosPlus = food_x + j;
                        for ( k = -1; (k <2 ) && !stopLoop; k++)
                        {
                            int yPosPlus = food_y + k;

                            if (food_exists(foods, xPosPlus, yPosPlus))
                                // if there is any kind of food in the vicinity, make the size & height * width == 1
                            {
                                if ( yPosPlus == food_y && xPosPlus == food_x)
                                {
                                    continue;
                                }
                                else
                                {
                                    new_food -> width = 1;
                                    new_food -> height = 1;
                                    stopLoop = true;
                                    surroundings = true;
                                    break;
                                }

                            }
                        }

                    }
                    if ( surroundings == true) // if there exists any kind of food in the vicinity, just make the obstacle size 1.
                    {
                        continue;
                    }
                    else    // if there isn't any kind of food/obstacles in the vicinity, we can make the size of the obstacle 2.
                    {
                        // there are 4 ways to make a shape of width x and height of y that conforms within the windows
                        // 1. (x,y), ( x + width,y), (x, y + height), (x+ width, y + height) from left to right, downwards
                        // 2. (x,y), (x + width,y), (x, y - height), (x+ width, y - height) from left to right, upwards
                        // 3. (x,y), ( x - width,y), (x, y + height), ( x - width, y + height)  from right to left, downwards
                        // 4. (x,y), (x - width,y), (x, y - height), ( x- width, y - height)    from right to left, upwards

                        // hence, we have to check if the x and y coordinates are inside the boundaries, and decide which way to implement the square

                        // case 1.
                        if (((new_food -> x ) <= x_offset + width - new_food-> width) && ((new_food -> y ) <= y_offset + height - new_food -> height))
                        {
                            for ( j = 0; j < new_food -> width; j++)
                            {
                                int xStart = new_food -> x + j;
                                for ( k = 0; k < new_food -> height; k++)
                                {
                                    int yStart = new_food -> y + k;
                                    Food* obstacle = create_food(xStart, yStart, type);
                                    add_new_food(foods, obstacle);
                                }
                            }
                        }
                        // case 2.
                        else if (((new_food -> x ) <= x_offset + width - new_food-> width) && ((new_food -> y ) >= y_offset + new_food -> height))
                        {
                            for ( j = 0; j < new_food -> width; j++)
                            {
                                int xStart = new_food -> x + j;
                                for ( k = 0; k < new_food -> height; k++)
                                {
                                    int yStart = new_food -> y - k;
                                    Food* obstacle = create_food(xStart, yStart, type);
                                    add_new_food(foods, obstacle);
                                }
                            }
                        }
                        // case 3.
                        else if (((new_food -> x ) >= x_offset + new_food-> width) && ((new_food -> y ) <= y_offset + height - new_food -> height))
                        {
                            for ( j = 0; j < new_food -> width; j++)
                            {
                                int xStart = new_food -> x - j;
                                for ( k = 0; k < new_food -> height; k++)
                                {
                                    int yStart = new_food -> y + k;
                                    Food* obstacle = create_food(xStart, yStart, type);
                                    add_new_food(foods, obstacle);
                                }
                            }

                        }
                        // case 4.
                        else if (((new_food -> x ) >= x_offset + new_food-> width) && ((new_food -> y ) >= y_offset + new_food -> height))
                        {
                            for ( j = 0; j < new_food -> width; j++)
                            {
                                int xStart = new_food -> x - j;
                                for ( k = 0; k < new_food -> height; k++)
                                {
                                    int yStart = new_food -> y - k;
                                    Food* obstacle = create_food(xStart, yStart, type);
                                    add_new_food(foods, obstacle);
                                }
                            }
                        }
                    }
                }

            }



            break;

        case ALIVE:

        ch = get_char();

	    if(ch == 'q' || ch == 'Q') //quit game case 
            {
                state = EXIT;
                break;
            }

        // code here is taken from Kent's milestone_1
            if ( ch == 'P' || ch == 'p')
            {
                char temp;
                while ( ch == 'P' || ch == 'p')
                {
                    mvprintw(14,10, "Game is paused.");
			        mvprintw(15,10, "Press 'q' or 'Q' to quit");//Quit the game
		    	    mvprintw(16,10, "Press 'p' or 'P' to unpause");//unpause the game
	            	mvprintw(17,10, "Press 'f' or 'F' to save");//save the game

                    refresh();
                    sleep(1);
                    temp = get_char();
                    if ( temp == 'P' || temp == 'p')
                    {
                        mvprintw(14,10, "Game is resumed.");
                        ch = get_char();
                        break;
                    }

                    if ( temp == 'q' || ch == 'Q') //quit game case
                    {
                        undraw_Gamewindow(window);
                        state = EXIT;
                        break;
                    }
		            if ( temp == 'f' || ch == 'F') //save game case
		            {
			        endwin();
			        printf("\nPlease input the file name you want to save this game to.\n");
			        scanf("%s", fileName);
			        strcat(filePath, fileName);
                    fp = fopen(filePath,"w");

                    thisGame.points = points;
                    thisGame.lives = lives;
                    thisGame.foodEaten = foodEaten;
                    thisGame.snake = snake;
                    thisGame.foods = foods;
                    thisGame.window = window;

                    //fwrite(&points, sizeof(int), 1, fp);
                    //fwrite(&lives, sizeof(int), 1, fp);
                    //fwrite(&foodEaten, sizeof(int), 1, fp);
                    //fwrite(&window, sizeof(window), 1,fp);
                    fwrite(&thisGame, sizeof(snake), 1,fp);
                    Snake *next, *snakeCopy;
                    snakeCopy = snake;
                    while ( snakeCopy != NULL)
                    {
                        next = snakeCopy ->next;
                        fseek(fp,0,SEEK_END);
                        //writing each body part of the snake to the file for saving
                        fwrite(snakeCopy, sizeof(Snake), 1, fp);
                        printf("Copying snake...\n");
                        snakeCopy -> next = next;
                        next = NULL;
                        snakeCopy = snakeCopy -> next;
                    }
                    /* while (snake != NULL)
                        {
                        next = snake->next;
                        struct Snake *newtail = create_tail(next->x, next->y);
                        thisGame.snake.next = newtail;
                        thisGame.snake.next->next = NULL;
                        snake = snake->next;
                        thisGame.snake = thisGame.snake
                        } */
                    fwrite(&thisGame, sizeof(struct save), 1, fp);
                    //implementing code to check if our output is correct, uncomment below code if you want
                    //please uncomment the fprintf code after testing since it will affect the output of our intended saved game state
                    //fprintf(fp, "\n points: %d lives: %d \n", thisGame.points, thisGame.lives);
                    fclose(fp);
                    state = EXIT;
                    break;
		            }

                }
            }

	    if(ch == '+' && (window->width != (width + 25))) //grow game case
            {
                window->width += 5;
		        window->height += 5;
            }

	    // implemented removing food if its out of the window, and adding new food
	    if(ch == '-' && (window->width != (width - 25))) //shrink game case
            {

                window->width -= 5;
                window->height -= 5;
                int tempWidth = window -> width, tempHeight = window -> height;
                Food* thisFood = foods;
                while (thisFood -> next != NULL)
                {

                    if ( thisFood -> x >= x_offset + tempWidth || thisFood -> y >= y_offset + tempHeight)
                    {

                        foods = remove_eaten_food(foods, foods -> x, foods -> y);
                        generate_points(&food_x, &food_y, window -> width, window -> height, x_offset, y_offset);
                        while (food_exists(foods,food_x, food_y))
                            generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                        type = (rand() > RAND_MAX/2) ? Increase : Decrease;
                        new_food = create_food(food_x, food_y, type);
                        add_new_food(foods, new_food);
                    }
                    thisFood =  thisFood -> next;
                }
            }
	   
	    if(ch != EOF) //if some input update prevCh 
	    {
		    prevCh = ch;
	    }

	    int toMove = rand() % 2;
	    int move1, move2;

	    if ( enemy1 == NULL)
        {
            free(enemy1);
        }

	    if ( enemy2 == NULL)
        {
	        free(enemy2);
        }

	    if ( toMove == 1)
	    {
	        move1 = rand() % 4 + 1;
	        prevChE1 = move1;
	        prevDirE1 = move1;
	        move2 = rand() % 4 + 1;
	        prevChE2 = move2;
	        prevDirE2 = move2;
	    }

	    if ( enemy1 != NULL)
        {
            enemy1 = move_snakeE1(enemy1, prevChE1);
        }

	    if ( enemy2 != NULL)
        {
            enemy2 = move_snakeE2(enemy2, prevChE2);
        }


	    snake = move_snake(snake, prevCh); //move snake

	    if(food_exists(foods, snake->x , snake->y)) //eat food
	    {
	        if ( food_type(foods, snake->x , snake->y) == Increase || food_type(foods, snake->x , snake->y) == Decrease)
            {
                if(food_type(foods, snake->x , snake->y) == Increase)
                {
                    points += 20; //updates points

                    Snake *new = create_tail(snake->x , snake->y); //grows snake
                    new->next = snake;
                    snake = new;
                }

                if (food_type(foods, snake->x , snake->y) == Decrease)
                {
                    points -= 10; //updates points
                    if(len(snake) == 1) //dies if length less than one
                    {
                        lives--;
                        state = DEAD;
                        break;
                    }

                    snake = remove_tail(snake); //shrinks snake
                }
                foodEaten++; //adds to eaten food
                foods = remove_eaten_food(foods, snake->x , snake->y); //removes food
                generate_points(&food_x, &food_y, window -> width, window -> height, x_offset, y_offset);
                while (food_exists(foods,food_x, food_y))
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                type = (rand() > RAND_MAX/2) ? Increase : Decrease; //adds new food
                new_food = create_food(food_x, food_y, type);
                add_new_food(foods, new_food);
            }
            // reversing snake movement when running into the obstacle
            if ( (food_type(foods, snake->x , snake->y) == Obstacle))
            {
                /*Snake *newHead, *end, *beforeEnd;
                int length = len(snake);
                int loop = 0;
                while (snake -> next != NULL)
                    end = snake -> next;
                end -> next = NULL;
                newHead = end;
                while ( loop < length - 1) //length - 1 since we already initialized the newHead
                {
                    Snake *tailSegment;
                    int traverse = 0;
                    while ( traverse != length - 1 - loop)
                    {
                        tailSegment = snake -> next;
                        traverse++;
                    }
                    tailSegment -> next = NULL;
                    newHead -> next = tailSegment;
                    loop++;
                }*/

                reverseMovement(snake, snake -> x, snake -> y, prevCh);

                if (prevCh == LEFT)
                {
                    prevCh = RIGHT;
	                prevDir = RIGHT;
                }
               if (prevCh == RIGHT)
                {
                    prevCh = LEFT;
                    prevDir = LEFT;
                }
                if (prevCh == UP)
                {
                    prevCh = DOWN;
                    prevDir = DOWN;
                }
                if (prevCh == DOWN)
                {
                    prevCh = UP;
                    prevDir = UP;
                }
                snake = move_snake(snake, prevCh);
            }
	    }

	    if(food_exists(foods, enemy1->x , enemy1->y) && enemy1 != NULL) //eat food for enemy1
	        {
                if (food_type(foods, enemy1->x, enemy1->y) == Increase || food_type(foods, enemy1->x, enemy1->y) == Decrease) {
                    if (food_type(foods, enemy1->x, enemy1->y) == Increase) {
                        Snake *new = create_tail(enemy1->x, enemy1->y); //grows snake
                        new->next = enemy1;
                        enemy1 = new;
                    }

                    if (food_type(foods, enemy1->x, enemy1->y) == Decrease) {

                        if (len(enemy1) == 1)
                        {
                            enemy1 = NULL;
                        }
                        if(len(enemy1) > 1)
                        {
                            enemy1 = remove_tail(enemy1); //shrinks snake
                        }
                    }

                    foods = remove_eaten_food(foods, enemy1->x , enemy1->y); //removes food
                    generate_points(&food_x, &food_y, window -> width, window -> height, x_offset, y_offset);
                    while (food_exists(foods,food_x, food_y))
                        generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                    type = (rand() > RAND_MAX/2) ? Increase : Decrease; //adds new food
                    new_food = create_food(food_x, food_y, type);
                    add_new_food(foods, new_food);
                }

                if ( (food_type(foods, enemy1->x , enemy1->y) == Obstacle))
                {
                    /*Snake *newHead, *end, *beforeEnd;
                    int length = len(snake);
                    int loop = 0;
                    while (snake -> next != NULL)
                        end = snake -> next;
                    end -> next = NULL;
                    newHead = end;
                    while ( loop < length - 1) //length - 1 since we already initialized the newHead
                    {
                        Snake *tailSegment;
                        int traverse = 0;
                        while ( traverse != length - 1 - loop)
                        {
                            tailSegment = snake -> next;
                            traverse++;
                        }
                        tailSegment -> next = NULL;
                        newHead -> next = tailSegment;
                        loop++;
                    }*/

                    if (prevChE1 == LEFT)
                    {
                        prevChE1 = RIGHT;
                        prevDirE1 = RIGHT;
                    }
                    if (prevChE1 == RIGHT)
                    {
                        prevChE1 = LEFT;
                        prevDirE1 = LEFT;
                    }
                    if (prevChE1 == UP)
                    {
                        prevChE1 = DOWN;
                        prevDirE1 = DOWN;
                    }
                    if (prevChE1 == DOWN) {
                        prevChE1 = UP;
                        prevDirE1 = UP;
                    }
                    reverseMovement(enemy1, enemy1 -> x, enemy1 -> y, move1);
                    enemy1 = move_snakeE1(enemy1, move1);
                }
            }

	    if(food_exists(foods, enemy2->x , enemy2->y)&& enemy2 != NULL) //eat food for enemy2
            {
                if (food_type(foods, enemy2->x, enemy2->y) == Increase || food_type(foods, enemy2->x, enemy2->y) == Decrease) {
                    if (food_type(foods, enemy2->x, enemy2->y) == Increase) {
                        Snake *new = create_tail(enemy2->x, enemy2->y); //grows snake
                        new->next = enemy2;
                        enemy2 = new;
                    }

                    if (food_type(foods, enemy2->x, enemy2->y) == Decrease) {

                        if (len(enemy2) == 1)
                        {
                            enemy2 = NULL;
                        }
                        if(len(enemy2) > 1)
                        {
                            enemy2 = remove_tail(enemy2); //shrinks snake
                        }

                    }

                    foods = remove_eaten_food(foods, enemy2->x , enemy2->y); //removes food
                    generate_points(&food_x, &food_y, window -> width, window -> height, x_offset, y_offset);
                    while (food_exists(foods,food_x, food_y))
                        generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                    type = (rand() > RAND_MAX/2) ? Increase : Decrease; //adds new food
                    new_food = create_food(food_x, food_y, type);
                    add_new_food(foods, new_food);
                }

                if ( (food_type(foods, enemy2->x , enemy2->y) == Obstacle))
                {
                    /*Snake *newHead, *end, *beforeEnd;
                    int length = len(snake);
                    int loop = 0;
                    while (snake -> next != NULL)
                        end = snake -> next;
                    end -> next = NULL;
                    newHead = end;
                    while ( loop < length - 1) //length - 1 since we already initialized the newHead
                    {
                        Snake *tailSegment;
                        int traverse = 0;
                        while ( traverse != length - 1 - loop)
                        {
                            tailSegment = snake -> next;
                            traverse++;
                        }
                        tailSegment -> next = NULL;
                        newHead -> next = tailSegment;
                        loop++;
                    }*/

                    reverseMovement(enemy2, enemy2 -> x, enemy2 -> y, move2);

                    if (prevChE2 == LEFT)
                    {
                        prevChE2 = RIGHT;
                        prevDirE2 = RIGHT;
                    }
                    if (prevChE2 == RIGHT)
                    {
                        prevChE2 = LEFT;
                        prevDirE2 = LEFT;
                    }
                    if (prevChE2 == UP)
                    {
                        prevChE2 = DOWN;
                        prevDirE2 = DOWN;
                    }
                    if (prevChE2 == DOWN) {
                        prevChE2 = UP;
                        prevDirE2 = UP;
                    }
                    enemy2 = move_snakeE2(enemy2, prevChE2);
                }
            }

	    //Snake *end = snake;

	   //while ( end != NULL){}

	    /*if (eat_itself(snake))
        {
            remove_tail(snake);
        }*/


	    if(foodEaten == 10)
	    {
		//speed up game
		timeret.tv_nsec *= 0.9;
		foodEaten = 0;//reset
	    }
	    if(snake -> x <= x_offset) //snake hits left wall
	        {
		        snake -> x = x_offset + width - 1;
	        }
	    if(snake -> x >= x_offset + width) //snake hits right wall
	        {
	            snake -> x = x_offset + 1;
            }
	    if(snake -> y <= y_offset) //snake hits top wall
            {
                snake -> y = y_offset + height - 1;
            }
	    if(snake -> y >= y_offset + height) //snake hits bottom wall
            {
                snake -> y = y_offset + 1;
            }

	    //if enemy1 hits any wall, move away

	    if(enemy1 -> x <= x_offset + 0.05*width) //enemy1 approaches left wall
            {
                move_snakeE1(enemy1, RIGHT);
            }
	    if(enemy1 -> x >= x_offset + 0.95*width) //enemy1 approaches right wall
            {
                move_snakeE1(enemy1, LEFT);
            }
	    if(enemy1 -> y <= y_offset + 0.05*height) //snake hits top wall
            {
                move_snakeE1(enemy1, DOWN);
            }
	    if(enemy1 -> y >= y_offset + 0.95*height) //snake hits bottom wall
            {
                move_snakeE1(enemy1, UP);
            }

	    //if enemy2 hits any wall, move away

	    if(enemy2 -> x <= x_offset + 0.05*width) //enemy1 approaches left wall
            {
                move_snakeE2(enemy2, RIGHT);
            }
	    if(enemy2 -> x >= x_offset + 0.95*width) //enemy1 approaches right wall
            {
                move_snakeE2(enemy2, LEFT);
            }
	    if(enemy2 -> y <= y_offset + 0.05*height) //snake hits top wall
            {
                move_snakeE2(enemy2, DOWN);
            }
	    if(enemy2 -> y >= y_offset + 0.95*height) //snake hits bottom wall
            {
                move_snakeE2(enemy2, UP);
            }

	    Snake* snakeBody = snake -> next;
	    Snake *snakeHead = snake;
	    snakeHead -> next = NULL;
	    if (snake_collision(snakeHead, snakeBody))
            {
                remove_tail(snake);
            }

        if (snake_collision(snake, enemy1) == true || snake_collision(snake, enemy2) == true)
        {
            state = DEAD;
        }


	    // Draw everything on the screen

	    clear();
	    mvprintw(0,0, "Points: %d", points);
	    mvprintw(1,0, "Lives: %d", lives);
	    mvprintw(10,10, "Press s to start and q or Q to stop");//Welcome screen with instructions
	    mvprintw(11,10, "Press p or P to pause");
	    mvprintw(12,10, "Use arrow keys to move (do not hold)");
	    mvprintw(13,10, "Use + and - respectively to resize");

	    //printing color for options on menu
            /* used to color the menu
            init_pair(3,COLOR_RED, COLOR_WHITE); //color selected option
            init_pair(4, COLOR_BLUE, COLOR_BLACK);  //color not selected options
             */
	    if ( difficulty == 'E' || difficulty == 'e')
        {
	        attron(COLOR_PAIR(3));
            mvprintw(15,10, "E/e for Easy,");
            attroff(COLOR_PAIR(3));

            attron(COLOR_PAIR(4));
            mvprintw(15,24, "H/h for Hard, V/v for Advanced");
            attroff(COLOR_PAIR(4));
        }

	    if ( difficulty == 'H' || difficulty == 'h')
        {
            attron(COLOR_PAIR(4));
            mvprintw(15,10, "E/e for Easy,");
            attroff(COLOR_PAIR(4));

            attron(COLOR_PAIR(3));
            mvprintw(15,24,"H/h for Hard,");
            attroff(COLOR_PAIR(3));

            attron(COLOR_PAIR(4));
            mvprintw(15,38, "V/v for Advanced");
            attroff(COLOR_PAIR(4));
        }

            if ( difficulty == 'V' || difficulty == 'v')
            {
                attron(COLOR_PAIR(4));
                mvprintw(15,10, "E/e for Easy, H/h for Hard,");
                attroff(COLOR_PAIR(4));

                attron(COLOR_PAIR(3));
                mvprintw(15,38," V/v for Advanced");
                attroff(COLOR_PAIR(3));
            }

	    mvprintw(20,20, "Key entered: %c", ch);
	    draw_Gamewindow(window);


            attron(COLOR_PAIR(2));  //snake
	        draw_snake(snake);
            attroff(COLOR_PAIR(2));  //snake

            attron(COLOR_PAIR(1));  //enemy1
	        draw_snake(enemy1);
            attroff(COLOR_PAIR(1)); //enemy1

            attron(COLOR_PAIR(5));  //enemy2
            draw_snake(enemy2);
            attroff(COLOR_PAIR(5));  //enemy2

            if ( snake2 != NULL)
            {
                attron(COLOR_PAIR(7));  //snake2
                draw_snake(snake2);
                attroff(COLOR_PAIR(7));  //snake2
            }



            attron(COLOR_PAIR(6));  //food & obstacles
            draw_food(foods);
            attroff(COLOR_PAIR(6));  //food & obstacles

	   
	   
	    break;

        case DEAD:
            clear();
            mvprintw(0,0, "Points: %d", points);
            mvprintw(1,0, "Lives: %d", lives);
            mvprintw(9,0, "Game over! You have %d amount of lives left.", lives);
            mvprintw(10,10, "Press r or R to restart");//Restart the game
	        mvprintw(11,10, "Press q or Q to quit");//Quit the game
            ch = get_char();
            if (lives >= 1 && ((ch == 'r') || (ch == 'R')))
            {
                state = INIT;
            }

            if ( lives == 0)
            {
                thisGame.maxHeap.newScore = points;
                update_heap(thisGame.maxHeap, points);
            }

            if ( ch == 'q' || ch == 'Q') //exit program
            {
                endwin();
                state = EXIT;
                break;
            }
            break;

	    case EXIT:

            exit(0);
            endwin();
            break;

	    case LOAD:

            mvprintw(13,10, "Press r or R to return to main menu");
            mvprintw(14,10, "Press q or Q to quit the game");
            mvprintw(15,10, "Press l or L to display the saved games in saves/ folder:");

            ch = get_char();


            if ( ch == 'r' || ch == 'R')
            {
                state = INIT;
                break;
            }

            if ( ch == 'Q' || ch == 'q')
            {
                state = EXIT;
                break;
            }

            if ( ch == 'Q' || ch == 'q' || ch == 'r' || ch == 'R')
            {
                break;
            }
            if (  ch == 'L' || ch == 'l')
            {
                endwin();
                clear();
                state = INIT_LOAD;

            }
            mvprintw(17,20, "Key entered: %c", ch);
	        break;

	    case INIT_LOAD:
	        endwin();
	        clear();
            char inputChar;

            printf("%s","Listed below are the saved games:\n");
            printf("%s", "game 1: game1.game\n");
            printf("%s", "game 2: game2.game\n");
            printf("%s", "game 3: game3.game\n");
            printf("%s", "game 4: game4.game\n");
            printf("%s", "game 5: game5.game\n");

            /*
             *  struct save
             *  {
             *      int points, lives, foodEaten;
             *      gamewindow_t *window;
             *      Snake *snake;
             *      Food *foods;
             *      maxHeap maxHeap;
             *  };
             */

            printf("%s","Please enter the file name of which game you wanted to load, as stated above\n");
            scanf("%s", input);
            strcat(filePath2, input);
            fp2 = fopen(filePath2, "r");

            //fp2 is the first read from user input, fp3 is the second read from user input.

            //ensuring input game file is correct. if not, start a new game.
            if ( fp2 == NULL)
            {
                printf("%s", "\nThe name of the file you have input is wrong. Please input the correct file name!\n---------------\n");
                count++;
                if (count == 1)
                {
                    printf("%s","Please enter the file name of which game you wanted to load, as stated above\n");
                    scanf("%s", input2);
                    strcat(filePath3, input2);
                    fp3 = fopen(filePath3,"r");
                    //if fp3 == NULL, start new game
                    if ( fp3 == NULL)
                    {
                        count++;
                        if ( count >= 2)
                        {
                            printf("\nSince you input the file name wrongly twice, a new game is started for you. Please enter s/S to start.\n");
                            scanf(" %c", &inputChar);
                            if ( inputChar == 's' || inputChar == 'S')
                            {
                                state = INIT;
                                break;
                            }

                        }

                    }
                    //else, open file and initialize the game.
                    else
                    {
                        rewind(fp3);
                        //read the file and load the saved game

                        fseek(fp3, 0, SEEK_END);
                        long snakeSize = ftell(fp3);
                        rewind(fp3);
                        int numSnakeBody = (int) (snakeSize / (sizeof(snake)));
                        int loop = 0;
                        for ( loop = 0; loop < numSnakeBody; loop++)
                        {
                            fseek(fp3, sizeof(Snake) * loop, SEEK_SET);
                            Snake *body = malloc(sizeof(Snake));

                        }

                        struct save init_game;
                        fread(&init_game, sizeof(struct save), 1,fp3);
                        //*window = init_game.window;
                        //*snake = init_game.snake;
                        //*foods = init_game.foods;
                        foodEaten = init_game.foodEaten;
                        lives = init_game.lives;
                        points = init_game.points;
                        heap = init_game.maxHeap;
                        draw_Gamewindow(window);
                        draw_snake(snake);
                        //initialize_maxHeap(heap);
                        state = ALIVE;
                    }
                }

            }

            else
            {

            }
            /*if (strcmp(input, "game1.game") == 0 || strcmp(input, "game2.game") == 0 || strcmp(input, "game3.game") == 0 || strcmp(input, "game4"
                                                                                                                                          ".game")
                                                                                                                            == 0 || strcmp(input, "game5.game") == 0 ) {


                initscr();
                start_color();
                nodelay(stdscr, TRUE); //Dont wait for char
                noecho(); // Don't echo input chars
                getmaxyx(stdscr, y_max, x_max);
                keypad(stdscr, TRUE); // making keys work
                curs_set(0); // hide cursor
                timeout(100);

                // Setting height and width of the board -> this sets the start point of the board, at coordinates (x_offset, y_offset)
                x_offset = (x_max / 2) - (width / 2);
                y_offset = (y_max / 2) - (height / 2);
            } */

	        break;
        }
        refresh();
        nanosleep(&timeret, NULL);
    }
    clear();
    endwin();

}
