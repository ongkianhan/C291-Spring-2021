/* key.c -------
 *
 * Filename: key.c
 * Description:
 * Author: Rishabh Agrawal
 * Maintainer: Gabriel Jude
 * Created: Sun Sep 13 20:29:30 2020
 * Last-Updated: September 13 22:39 2020
 *           By: Rishabh Agrawal
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

/* Copyright (c) 2016 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */


#include <ncurses.h>
#include <stdlib.h>
#include "key.h"

// added WASD for multiplayer

int get_char(){
  int ch = getch();
  switch(ch){
    case KEY_LEFT:
    case 'a':
      return LEFT;
      break;
    case KEY_RIGHT:
    case 'd':
      return RIGHT;
      break;
    case KEY_UP:
    case 'w':
      return UP;
      break;
    case KEY_DOWN:
    case 's':
      return DOWN;
      break;
    default:
      return(ch);
      break;
  }
}
