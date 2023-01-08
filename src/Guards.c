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

/*essayer de gerer la colision avec les angles de vues et le toucher du garde*/
int detection(Engine_Obj guard, Engine_Obj player) {
    double d;

    d = distance_between_objects(guard, player);

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

void move_guard(Engine_Guard *guard, Engine_Walls walls, int nb_walls) {
    float change_direction;

    change_direction = rand() % PROB_NEXT_DIRECTION_GUARD;

    /* 1/50 chance to change direction */
    if (change_direction == 1 || guard->direction == OBJECT_NONE) {
        guard->direction = guard_direction();
    }

    move_object(&(guard->obj), guard->direction, guard->speed);

    if (wall_collision(guard->obj, walls, nb_walls)) {
        move_object(&(guard->obj), OBJECT_REVERT, 0);
        move_guard(guard, walls, nb_walls);
    }
}