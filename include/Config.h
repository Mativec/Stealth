/**
 * @file const.h
 * @author VECCHIO Matias & ARNAOUT Richard
 * @brief Stock les reglages du jeu.
 * @version 0.1
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __CONST
#define __CONST

#define NAME "SLEATH"
#define ICON "res/image"

#define MOVE_UP MLV_KEYBOARD_z
#define MOVE_LEFT MLV_KEYBOARD_q
#define MOVE_RIGHT MLV_KEYBOARD_d
#define MOVE_DOWN MLV_KEYBOARD_s

#define SIZE_X 60 /* XSize of the game area */
#define SIZE_Y 45 /* YSize of the game area */
#define SCALE 20  /* Difference on size between game and it's graphical representation */

#define PROB_NEXT_DIRECTION_GUARD 50 /* 1/x chance to change a guard's direction */

#define SPEED 0.03                       /* Speed of all objects */
#define MAX_SPEED_PLAYER 0.9             /*Speed of the player*/
#define MAX_SPEED_PLAYER_OVERCHARGED 1.2 /*Speed changed at the time of events*/

#define MAX_MANA 5000    /*Mana gauge*/
#define MANA_PER_TUILE 2 /* Consomation of mana */

#define SIZE_PLAYER 0.5 /* Size of player cursor*/
#define BASE_PLAYER_X 5 /*Size of player's base X*/
#define BASE_PLAYER_Y 5 /*Size of player's base Y*/
#define SIZE_GUARD 10   /* Size of guard cursor*/
#define SIZE_WALL 1     /*Wall thickness*/

#define SIGHT_GUARDIAN 4 /*Vision of guard*/

#define TIMER_PANIC 30         /* Time of panic mode in secondes */
#define SIGHT_GUARDIAN_PANIC 6 /*Vision of guard in panic mode*/

#define NB_RELIQUES 3
#define NB_GUARDS 5

#endif
