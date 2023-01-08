/**
 * @file Guards.c
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Implémentation du module des gardes
 * @version 0.1
 * @date 2022-11-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../include/Guards.h"

Engine_Guard *init_guard(int x, int y) {
    Engine_Guard *new;

    new = (Engine_Guard *)malloc(sizeof(Engine_Guard));

    if (new != NULL) {
        new->obj = *init_object(x, y);
        new->direction = OBJECT_NONE;

        /* Speed between 0.3 & 0.8 -> don't change beside panic mode */
        new->speed = (double)((rand() % 6) + 3) / 10;
    }
    return new;
}

/*
int detection(Engine_Obj guard, Engine_Obj player) {
    return distance_between_objects(guard, player) < SIGHT_GUARDIAN;
}
*/

int detection(Engine_Obj guard, Engine_Obj player, Engine_Walls walls, int nb_walls) {
    Engine_Obj **voisins;
    int i;

    if(distance_between_objects(guard, player) < SIGHT_GUARDIAN){

        voisins = (Engine_Obj **)malloc(sizeof(Engine_Obj*) * 6);
        if(voisins != NULL){
            voisins[0] = init_object(player.x + 1, player.y);
            voisins[1] = init_object(player.x, player.y + 1);
            voisins[2] = init_object(player.x - 1, player.y);
            voisins[3] = init_object(player.x, player.y - 1);
            voisins[4] = init_object(player.x + 1, player.y + 1);
            voisins[5] = init_object(player.x - 1, player.y - 1);
            
            for(i = 0; i < 6; i++){
                if(wall_collision(*(voisins[i]), walls, nb_walls)){
                    return 0;
                }
            }
        }
        return 1;
    }
    return 0;
}

Engine_Orientation guard_direction() {
    int direction;

    direction = rand() % 4;
    switch (direction) {
        case 0:
            return OBJECT_UP;
        case 1:
            return OBJECT_LEFT;
        case 2:
            return OBJECT_DOWN;
        case 3:
            return OBJECT_RIGHT;
    }
    return OBJECT_NONE;
}

void move_guard(Engine_Guard *guard, Engine_Walls walls, int nb_walls) {
    float change_direction;

    change_direction = rand() % PROB_NEXT_DIRECTION_GUARD;

    if (change_direction == 1 || guard->direction == OBJECT_NONE) {
        guard->direction = guard_direction();
    }

    move_object(&(guard->obj), guard->direction, guard->speed);

    if (wall_collision(guard->obj, walls, nb_walls)) {
        move_object(&(guard->obj), OBJECT_REVERT, 0);
        move_guard(guard, walls, nb_walls);
    }
}