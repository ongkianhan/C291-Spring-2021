#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "food.h"
#include "game_window.h"
#include "key.h"
#include "game.h"
void generate_points(int *food_x, int *food_y, int width, int height, int x_offset, int y_offset){
    *food_x = rand() % width + x_offset;
    *food_y = rand() % height + y_offset;
}
void game() {
    enum State state = INIT; // Set the initial state
    static int x_max, y_max; //Max screen size variables
    static int x_offset, y_offset; // distance between the top left corner of your screen and the start of the board
    gamewindow_t *window; // Name of the board
    Snake *snake; // The snake
    Food *foods, *new_food; // List of foods (Not an array)

    const int height = 30;
    const int width = 70;
    char ch;
    char prevChar = RIGHT;
    int points = 0, numEaten = 0;

    struct timespec timeret;
    timeret.tv_sec = 0;
    timeret.tv_nsec = 999999999 / 4;

    while (state != EXIT) {
        switch (state) {
            case INIT:
                initscr();
                start_color();
                nodelay(stdscr, TRUE); //Dont wait for char
                noecho(); // Don't echo input chars
                getmaxyx(stdscr, y_max, x_max);
                keypad(stdscr, TRUE); // making keys work
                curs_set(0); // hide cursor
                timeout(100);

                // Setting height and width of the board
                x_offset = (x_max / 2) - (width / 2);
                y_offset = (y_max / 2) - (height / 2);

                //Init board
                window = init_GameWindow(x_offset, y_offset, width, height);
                draw_Gamewindow(window);

                // Init snake
                snake = init_snake(x_offset + (width / 2), y_offset + (height / 2));

                // Init foods
                int food_x, food_y, i;
                enum Type type;

                //Generate 20 foods
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                type = (rand() > RAND_MAX / 2) ? Increase : Decrease; // Randomly deciding type of food
                foods = create_food(food_x, food_y, type);
                for (i = 1; i < 20; i++) {
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                    while (food_exists(foods, food_x, food_y))
                        generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                    type = (rand() > RAND_MAX / 2) ? Increase : Decrease;
                    new_food = create_food(food_x, food_y, type);
                    add_new_food(foods, new_food);
                }
                state = ALIVE;

                break;

            case ALIVE:
                ch = get_char();

                /* Write your code here */

                if (ch == 'q' || ch == 'Q') //quit the game
                {
                    state = EXIT;
                    exit(0);
                    break;
                }

                if (ch == 'P' || ch == 'p') {
                    char temp;
                    while (ch == 'P' || ch == 'p') {
                        mvprintw(14, 10, "Game is paused.");
                        refresh();
                        sleep(1);
                        temp = get_char();
                        if (temp == 'P' || temp == 'p') {
                            mvprintw(14, 10, "Game is resumed.");
                            ch = get_char();
                            break;
                        }

                        if (temp == 'q' || ch == 'Q') //quit game case
                        {
                            exit(0);
                            break;
                        }
                    }
                }

                if (ch == '+' && (window->width != (width + 25))) //grow game case
                {
                    window->width += 5;
                    window->height += 5;
                }

                // implemented removing food if its out of the window, and adding new food
                if (ch == '-' && (window->width != (width - 25))) //shrink game case
                {

                    window->width -= 5;
                    window->height -= 5;
                    int tempWidth = window->width, tempHeight = window->height;
                    Food *thisFood = foods;
                    while (thisFood->next != NULL) {

                        if (thisFood->x >= x_offset + tempWidth || thisFood->y >= y_offset + tempHeight) {

                            foods = remove_eaten_food(foods, foods->x, foods->y);
                            generate_points(&food_x, &food_y, window->width, window->height, x_offset, y_offset);
                            while (food_exists(foods, food_x, food_y))
                                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                            type = (rand() > RAND_MAX / 2) ? Increase : Decrease;
                            new_food = create_food(food_x, food_y, type);
                            add_new_food(foods, new_food);
                        }
                        thisFood = thisFood->next;
                    }
                }

                if (ch != EOF) {
                    prevChar = ch;
                }


                snake = move_snake(snake, prevChar); //move snake
                if (food_exists(foods, snake->x, snake->y)) //eat food
                {
                    if (food_type(foods, snake->x, snake->y) == Increase || food_type(foods, snake->x, snake->y) == Decrease) {
                        if (food_type(foods, snake->x, snake->y) == Increase) {
                            points += 20; //updates points

                            Snake *new = create_tail(snake->x, snake->y); //grows snake
                            new->next = snake;
                            snake = new;
                        }

                        if (food_type(foods, snake->x, snake->y) == Decrease) {
                            points -= 10; //updates points
                            snake = remove_tail(snake); //shrinks snake
                        }
                        numEaten++; //adds to eaten food
                        foods = remove_eaten_food(foods, snake->x, snake->y); //removes food
                        generate_points(&food_x, &food_y, window->width, window->height, x_offset, y_offset);
                        while (food_exists(foods, food_x, food_y))
                            generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                        type = (rand() > RAND_MAX / 2) ? Increase : Decrease; //adds new food
                        new_food = create_food(food_x, food_y, type);
                        add_new_food(foods, new_food);
                    }
                }
                //speed up the game if numEaten == 10;
                if (numEaten == 10) {
                    timeret.tv_nsec *= 0.8;
                    //reset numEaten
                    numEaten = 0;
                }

                // Draw everything on the screen
                clear();
                char menu[] = "Welcome to Kent's snake game!\nIn this game, try to eat as much growing food(O) and eat less junk food (X) and get as "
                              "many points as possible!\nControls:\nPress s to start the game.\nUse your arrow keys to move the snake around"
                              ".\nPress P or p to pause the game. Press P or p again to resume the game.\nPress Q or q at any time to quit the game"
                              ".\nPress + to increase the game window size, and - to decrease the game window size.\n";

                mvprintw(0, 0, "Points: %d", points);
                mvprintw(10, 20, "%s", menu);
                mvprintw(20, 20, "Key entered: %c", ch);
                draw_Gamewindow(window);
                draw_snake(snake);
                draw_food(foods);
                break;

            case DEAD:
                endwin();
                break;
        }
        refresh();
        nanosleep(&timeret, NULL);
    }
    clear();
    endwin();
}