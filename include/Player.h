/**
 * @file Player.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __PLAYER
#define __PLAYER

#include <string.h>

#include "Config.h"
#include "Input.h"
#include "Object.h"

typedef struct __player {
    Engine_Obj obj;
    Engine_Orientation orientation;
    int score;
    int mana;
    int overcharge;
    int invisibility;
    double speed;
} Engine_Player;



/**
 * @brief initializes the player to a position given in parameter
 * 
 * @param x 
 * @param y 
 * @return Engine_Player* 
 */
Engine_Player *init_player(double x, double y);


/**
 * @brief fuction allows the movement of the player
 * 
 * @param player 
 * @param input 
 */
void move_player(Engine_Player *player, Engine_Input input);



/**
 * @brief retuns player's object and player orientation in string
 * 
 * @param player 
 * @param player_name 
 * @return char* 
 */
char *player_to_string(Engine_Player player, char *player_name);

#endif
