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
    double speed;
} Engine_Player;

Engine_Player *init_player(double x, double y);

void move_player(Engine_Player *player, Engine_Input input);

char *player_to_string(Engine_Player player, char *player_name);

#endif
