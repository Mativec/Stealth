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

Engine_Player *init_player(double x, double y){
    Engine_Player * new;

    new = (Engine_Player *)malloc(sizeof(Engine_Player));
    if(new == NULL){
        fprintf(stderr, "Failed to init Player...\n");
        exit(EXIT_FAILURE);
    }
    new->obj = *init_object(x, y);
    new->orientation = OBJECT_NONE;
    new->mana = MAX_MANA;
    new->score = 0;
    new->speed = 0;

    return new;
}

void move_player(Engine_Player *player, Engine_Input way) {
    Engine_Orientation orientation;

    orientation = input_to_orientation(way);

    if(orientation != OBJECT_NONE){
        if(orientation != player->orientation){
            player->speed = 0.1;
            player->orientation = orientation;
        }
        else{
            player->speed += 0.03;
        }
        
        if(player->speed > MAX_SPEED_PLAYER){
            player->speed = MAX_SPEED_PLAYER;
        }

        move_object(&(player->obj), player->orientation, player->speed);
    }
}


char *player_to_string(Engine_Player player, char *player_name){
    char * output;

    output = (char *)malloc(sizeof(char) * 64);

    sprintf(
        output, "%s, %s, %f, %d, %d\n",
        object_to_string(player.obj),
        orientation_to_string(player.orientation),
        player.speed, player.mana, player.score
    );

    return output;
}