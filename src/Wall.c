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

Engine_Wall *init_wall(float x, float y, Engine_Orientation way, int size) {
    Engine_Wall *new_wall;
    Engine_Obj * obj;

    new_wall = (Engine_Wall *)malloc(sizeof(Engine_Wall));

    if (new_wall != NULL) {
        obj = init_object(x, y);

        new_wall->obj = *obj;
        new_wall->orientation = way;
        new_wall->size = size;

        free(obj);
    }
    return new_wall;
}

void add_wall(Engine_Walls *walls, int *nb_wall, Engine_Wall wall) {
    static int buffer = 0;

    assert(walls != NULL);
    assert(nb_wall != NULL);

    /* 1st wall to add ? */
    if (buffer == 0) {
        /* 4 walls minimum (border) */
        buffer = 4;
        *walls = (Engine_Walls)malloc(sizeof(Engine_Wall) * buffer);
    }

    if(*nb_wall >= buffer){
        while ((*nb_wall) >= buffer) {
            buffer *= 2;
        }
        *walls = realloc(*walls, sizeof(Engine_Wall) * buffer);
    }
    if ((*walls) == NULL) {
        fprintf(stderr, "failed to create a wall...");
        exit(EXIT_FAILURE);
    }

    (*walls)[(*nb_wall)] = wall;
    (*nb_wall)++;
}

Engine_Walls generate_walls(int nb_walls) {
    return NULL;
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

int wall_collision(Engine_Obj obj, Engine_Walls walls, int nb_walls) {
    int i, collision;
    int *obj_coord, *wall_coord;

    assert(walls != NULL);

    collision = 0;
    obj_coord = get_object_coord(obj);

    for (i = 0; i < nb_walls; i++) {
        wall_coord = get_object_coord(walls[i].obj);
        /* on the same line ? horizontally */
        if (obj_coord[0] == wall_coord[0]){
            /* obj is between origine and limit of the wall ? Based on it's orientation. */
            if(walls[i].orientation == OBJECT_UP){
                if((obj_coord[1] <= wall_coord[1]) && (obj_coord[1] > wall_coord[1] - walls[i].size)){
                    collision = 1;
                }
            }
            else if(walls[i].orientation == OBJECT_DOWN){
                if((obj_coord[1] >= wall_coord[1]) && (obj_coord[1] < wall_coord[1] + walls[i].size)){
                    collision = 1;
                }
            }
        }
        /* on the same line ? vertically */
        else if (obj_coord[1] == wall_coord[1]){
            /* obj is between origine and limit of the wall ? Based on it's orientation. */
            if(walls[i].orientation == OBJECT_LEFT){
                if((obj_coord[0] <= wall_coord[0]) && (obj_coord[0] > wall_coord[0] - walls[i].size)){
                    collision = 1;
                }
            }
            else if(walls[i].orientation == OBJECT_RIGHT){
                if((obj_coord[0] >= wall_coord[0]) && (obj_coord[0] < wall_coord[0] + walls[i].size)){
                    collision = 1;
                }
            }
        }
    }
    free(obj_coord);
    free(wall_coord);
    return collision;
}

void free_walls(Engine_Walls walls, int * nb_walls){
    assert(walls != NULL);
    assert(nb_walls != NULL);

    free(walls);
    *nb_walls = 0;
}