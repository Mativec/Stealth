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

Engine_Obj *init_object(double x, double y) {
    Engine_Obj *new;

    new = (Engine_Obj *)malloc(sizeof(Engine_Obj));

    if (new != NULL) {
        new->x = x;
        new->y = y;
    }
    return new;
}

void move_object(Engine_Obj *obj, Engine_Orientation way) {
    static double base_x, base_y;

    if (way == OBJECT_REVERT) {
        obj->x = base_x;
        obj->y = base_y;
    } else {
        base_x = obj->x;
        base_y = obj->y;
        switch (way) {
            case OBJECT_UP:
                obj->y -= SPEED;
                break;
            case OBJECT_LEFT:
                obj->x -= SPEED;
                break;
            case OBJECT_RIGHT:
                obj->x += SPEED;
                break;
            case OBJECT_DOWN:
                obj->y += SPEED;
                break;
            default:
                break;
        }
    }
}

int *get_object_coord(Engine_Obj obj) {
    int *coords;

    coords = (int *)malloc(sizeof(int) * 2);
    if (coords != NULL) {
        coords[0] = (int)obj.x;
        coords[1] = (int)obj.y;
    }
    return coords;
}

char *object_to_string(Engine_Obj obj) {
    int *coord;
    char *output;

    output = (char *)malloc(sizeof(char) * 64);
    coord = get_object_coord(obj);

    sprintf(output, "(%d, %d)", coord[0], coord[1]);

    free(coord);
    return output;
}


double distance_between_objects(Engine_Obj obj1, Engine_Obj obj2){
    int *coord1, *coord2;
    coord1 = get_object_coord(obj1);
    coord2 = get_object_coord(obj2);
  return sqrt(pow(coord1[0] - coord2[0], 2) + pow(coord1[1] - coord2[1], 2));
}
