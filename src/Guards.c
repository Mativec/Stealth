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

int in_fov_guard(Engine_Guard guard, Engine_Obj target, int panic_mode) {
    int d;

    d = distance_between_objects(guard.obj, target);
    return panic_mode? d < SIGHT_GUARDIAN_PANIC : d < SIGHT_GUARDIAN;
}

int detection_axis_y(Engine_Guard guard, Engine_Obj target, Engine_Walls walls, int nb_walls){
    Engine_Obj * tmp;
    double a, pa, ya;

    a = guard.obj.x;
    pa = 0;
    while(pa >= 0 && pa <= 1){
        pa = (a - guard.obj.x) / (target.x - guard.obj.x);
        ya = pa * guard.obj.y + (1 - pa) * target.y;
        tmp = init_object(a, abs(ya));
        a -= 1;
        /* 
        fprintf(stderr, "G:%s & Tmp1:%s & Targ:%s\n", object_to_string(guard), object_to_string(tmp), object_to_string(target));
        fprintf(stderr, "t1 : %d\n", wall_collision(tmp, walls, nb_walls));
        getc(stdin);
        */
        if(wall_collision(*tmp, walls, nb_walls)){
            free(tmp);
            return 0;
        }
    }
    free(tmp);
    return 1;
}

int detection_axis_x(Engine_Guard guard, Engine_Obj target, Engine_Walls walls, int nb_walls){
    Engine_Obj *tmp;
    double b, pb, xb;

    b = guard.obj.y;
    pb = 0;
    while(pb >= 0 && pb <= 1){
        pb = (b - guard.obj.y) / (target.y - guard.obj.y);
        xb = pb * guard.obj.x + (1 - pb) * target.x;
        tmp = init_object(abs(xb), b);
        b += 1;
        /* 
        fprintf(stderr, "G:%s & Tmp1:%s & Targ:%s\n", object_to_string(guard), object_to_string(tmp), object_to_string(target));
        fprintf(stderr, "t1 : %d\n", wall_collision(tmp, walls, nb_walls));
        getc(stdin);
        */
        if(wall_collision(*tmp, walls, nb_walls)){
            free(tmp);
            return 0;
        }
    }
    free(tmp);
    return 1;
}

int detection(Engine_Guard guard, Engine_Obj target, int panic_mode, Engine_Walls walls, int nb_walls) {

    if(in_fov_guard(guard, target, panic_mode)){
        return
        detection_axis_y(guard, target, walls, nb_walls)
        &&
        detection_axis_x(guard, target, walls, nb_walls)
        ;
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
            if(in_fov_guard(*guard, walls[i].obj, panic_mode)){
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

    (*guards)[0] = *init_guard(33, 25);
    (*guards)[1] = *init_guard(35, 40);

    *nb_guards = 2;
}