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
        new->speed = 0;
    }
    return new;
}

/*essayer de gerer la colision avec les angles de vues et le toucher du garde*/
int detection(Engine_Obj guard, Engine_Obj target) {
    double d;

    d = distance_between_objects(guard, target);

    if (d < SIGHT_GUARDIAN - SIZE_PLAYER) {
        return 1;
    } else if (d < SIZE_PLAYER - SIGHT_GUARDIAN) {
        return 1;
    } else if (d <= SIGHT_GUARDIAN + SIZE_PLAYER) {
        return 1;
    } else {
        return 0;
    }
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

double guard_speed(){
    return (double)((rand() % 6) + 3) / 10;
}

void move_guard(Engine_Guard *guard, Engine_Walls walls, int nb_walls) {
    float change_direction;

    change_direction = rand() % PROB_NEXT_DIRECTION_GUARD;
    if(guard->speed == 0){
        guard->speed = guard_speed();
    }

    /* 1/50 chance to change direction */
    if (change_direction == 1 || guard->direction == OBJECT_NONE) {
        guard->direction = guard_direction();
    }

    move_object(&(guard->obj), guard->direction, guard->speed);

    if (wall_collision(guard->obj, walls, nb_walls)) {
        /* cancel movement */
        move_object(&(guard->obj), OBJECT_REVERT, 0);

        /* reset guard's property */
        guard->direction = OBJECT_NONE;
        guard->speed = 0;

        /* retry a movement */
        move_guard(guard, walls, nb_walls);
    }
}

void generate_guards(Engine_Guard ** guards, int *nb_guards){

    *guards = (Engine_Guard*)malloc(sizeof(Engine_Guard) * 5);

    (*guards)[0] = *init_guard(25, 25);
    (*guards)[1] = *init_guard(30, 30);

    *nb_guards = 2;
}