/**
 * @file Wall.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../include/Wall.h"

Wall *init_wall(float x, float y, Engine_Orientation way, int size) {
    Wall *new_wall;

    new_wall = (Wall *)malloc(sizeof(Wall));

    if (new_wall != NULL) {
        new_wall->coord = *init_object(x, y);
        new_wall->orientation = way;
        new_wall->size = size;
    }
    return new_wall;
}

void add_wall(Walls *walls, int *nb_wall, Wall wall) {
    static int buffer = 0;

    assert(walls);
    assert(nb_wall);

    if (buffer == 0) {
        buffer = 4;
        *walls = (Walls)malloc(sizeof(Wall) * buffer);
    }

    while ((*nb_wall) >= buffer) {
        buffer *= 2;
        *walls = realloc(*walls, sizeof(Wall) * buffer);
    }
    if ((*walls) != NULL) {
        (*walls)[(*nb_wall)] = wall;
        (*nb_wall)++;
    }
}

Walls generate_walls(int nb_walls) {
    return NULL;
}

char *orientation_to_string(Engine_Orientation orientation){
    switch (orientation)
    {
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
    default :
        return "";
    }
}

void wall_collision(Engine_Obj *obj) {
    int *coords;

    coords = get_object_coord(*obj);
    if (coords[0] <= 0 || coords[0] >= (SIZE_X - 1) || coords[1] <= 0 || coords[1] >= (SIZE_Y - 1)) {
        move_object(obj, OBJECT_REVERT);
    }
}
