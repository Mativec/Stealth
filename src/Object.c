/**
 * @file Object.c
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Base management for all game objects (source)
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

void move_object(Engine_Obj *obj, Engine_Orientation way, double factor) {
    static double base_x, base_y;

    if (way == OBJECT_REVERT) {
        obj->x = base_x;
        obj->y = base_y;
    } else {
        base_x = obj->x;
        base_y = obj->y;
        switch (way) {
            case OBJECT_UP:
                obj->y -= factor * SPEED;
                break;
            case OBJECT_LEFT:
                obj->x -= factor * SPEED;
                break;
            case OBJECT_RIGHT:
                obj->x += factor * SPEED;
                break;
            case OBJECT_DOWN:
                obj->y += factor * SPEED;
                break;
            default:
                break;
        }
    }
}

void get_object_coord(Engine_Obj obj, int coords[2]) {
    coords[0] = (int)obj.x;
    coords[1] = (int)obj.y;
}

char *object_to_string(Engine_Obj obj) {
    int coord[2];
    char *output;

    output = (char *)malloc(sizeof(char) * 64);
    get_object_coord(obj, coord);

    sprintf(output, "(%d, %d)", coord[0], coord[1]);

    return output;
}

int distance_between_objects(Engine_Obj obj1, Engine_Obj obj2) {
    int coord1[2], coord2[2];

    get_object_coord(obj1, coord1);
    get_object_coord(obj2, coord2);

    return sqrt(pow(coord1[0] - coord2[0], 2) + pow(coord1[1] - coord2[1], 2));
}

int contact_between_objects(Engine_Obj obj1, Engine_Obj obj2) {
    int coord1[2], coord2[2];

    get_object_coord(obj1, coord1);
    get_object_coord(obj2, coord2);

    return (coord1[0] == coord2[0]) && (coord1[1] == coord2[1]);
}

char *orientation_to_string(Engine_Orientation orientation) {
    switch (orientation) {
        case OBJECT_UP:
            return "Up";

        case OBJECT_LEFT:
            return "Left";

        case OBJECT_DOWN:
            return "Down";

        case OBJECT_RIGHT:
            return "Right";

        case OBJECT_REVERT:
            return "Revert";

        case OBJECT_NONE:
            return "None";

        default:
            return "";
    }
}