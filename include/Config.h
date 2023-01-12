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

#define NAME "Game"
#define ICON NULL

#define MOVE_UP MLV_KEYBOARD_z
#define MOVE_LEFT MLV_KEYBOARD_q
#define MOVE_RIGHT MLV_KEYBOARD_d
#define MOVE_DOWN MLV_KEYBOARD_s

#define SIZE_X 60 /* XSize of the game area */
#define SIZE_Y 45 /* YSize of the game area */
#define SCALE 20 /* Difference on size between game and it's graphical representation */

#define PROB_NEXT_DIRECTION_GUARD 50 /* 1/x chance to change a guard's direction */

#define SPEED 0.04 /* Speed of all objects */
#define MAX_SPEED_PLAYER 0.9
#define MAX_SPEED_PLAYER_OVERCHARGED 1.2

#define MAX_MANA 5000
#define MANA_PER_TUILE 2

#define SIZE_PLAYER 0.5
#define BASE_PLAYER_X 5
#define BASE_PLAYER_Y 5
#define SIZE_GUARD 10
#define SIZE_WALL 1

#define SIGHT_GUARDIAN 4

#define TIMER_PANIC 30 /* secondes */
#define SIGHT_GUARDIAN_PANIC 6



#endif
