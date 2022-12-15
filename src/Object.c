/**
 * @file Object.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../include/Object.h"

Engine_Obj *init_object(float x, float y, int speed) {
    Engine_Obj *new;

    new = (Engine_Obj *)malloc(sizeof(Engine_Obj));

    if (new != NULL) {
        new->x = x;
        new->y = y;
        new->speed = speed;
    }
    return new;
}

void move_object(Engine_Obj *obj, Engine_Orientation way) {
    static int base_x, base_y;

    if (way == OBJECT_REVERT) {
        obj->x = base_x;
        obj->y = base_y;
    } else {
        base_x = obj->x;
        base_y = obj->y;
        switch (way) {
            case OBJECT_UP:
                obj->y -= obj->speed;
                break;
            case OBJECT_LEFT:
                obj->x -= obj->speed;
                break;
            case OBJECT_RIGHT:
                obj->x += obj->speed;
                break;
            case OBJECT_DOWN:
                obj->y += obj->speed;
                break;
            default:
                break;
        }
    }
}

char *object_to_string(Engine_Obj obj) {
    return NULL;
}


double distance_between_objects(Engine_Obj obj1, Engine_Obj obj2){
  return sqrt((obj1.x - obj2.x) * (obj1.x - obj2.x) + (obj1.y - obj2.y) * (obj1.y - obj2.y));
}