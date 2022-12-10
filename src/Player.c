/**
 * @file Player.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../include/Player.h"

void move_player(Engine_Obj *player, Input way) {
    switch (way) {
        case INPUT_UP:
            move_object(player, OBJECT_UP);
            break;
        case INPUT_LEFT:
            move_object(player, OBJECT_LEFT);
            break;
        case INPUT_RIGHT:
            move_object(player, OBJECT_RIGHT);
            break;
        case INPUT_DOWN:
            move_object(player, OBJECT_DOWN);
            break;
        default:
            break;
    }
}