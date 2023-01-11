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

int detection(Engine_Guard guard, Engine_Obj target, int panic_mode) {
    int d;

    d = distance_between_objects(guard.obj, target);

    return panic_mode? d < SIGHT_GUARDIAN_PANIC : d < SIGHT_GUARDIAN;
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

double guard_speed(int panic_mode){
    double speed;

    speed = panic_mode? 1 : (double)((rand() % 6) + 3) / 10;

    return speed;
}

void move_guard(Engine_Guard *guard, int panic_mode, Engine_Walls walls, int nb_walls) {
    int i;

    if(guard->speed == 0 || panic_mode || guard->speed == 1){
        guard->speed = guard_speed(panic_mode);
    }

    /* 1/50 chance to change direction */
    if (guard->direction == OBJECT_NONE || (rand() % PROB_NEXT_DIRECTION_GUARD) == 1 ) {
        guard->direction = guard_direction();
    }

    move_object(&(guard->obj), guard->direction, guard->speed);

    if (!panic_mode && wall_collision(guard->obj, walls, nb_walls)) {
        /* cancel movement */
        move_object(&(guard->obj), OBJECT_REVERT, 0);

        /* reset guard's property */
        guard->direction = OBJECT_NONE;
        guard->speed = 0;

        /* retry a movement */
        move_guard(guard, panic_mode, walls, nb_walls);
    }
    else if(panic_mode){
        for (i = 0; i < nb_walls; i++){
            if(detection(*guard, walls[i].obj, panic_mode)){
                /* cancel movement */
                move_object(&(guard->obj), OBJECT_REVERT, 0);

                /* reset guard's property */
                guard->direction = OBJECT_NONE;
                guard->speed = 0;

                /* retry a movement */
                move_guard(guard, panic_mode, walls, nb_walls);
                return;
            }
        }
    }
}

void generate_guards(Engine_Guard ** guards, int *nb_guards){

    *guards = (Engine_Guard*)malloc(sizeof(Engine_Guard) * 5);

    (*guards)[0] = *init_guard(25, 25);
    (*guards)[1] = *init_guard(30, 30);

    *nb_guards = 2;
}