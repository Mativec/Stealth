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
    Engine_Obj *obj;

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

void add_wall(Engine_Walls *walls, int *nb_walls, Engine_Wall wall) {
    static int buffer = 0;

    assert(walls != NULL);
    assert(nb_walls != NULL);

    /* 1st wall to add ? */
    if (buffer == 0) {
        /* 4 walls minimum (border) */
        buffer = 4;
        *walls = (Engine_Walls)malloc(sizeof(Engine_Wall) * buffer);
    }

    if (*nb_walls >= buffer) {
        while ((*nb_walls) >= buffer) {
            buffer *= 2;
        }
        *walls = realloc(*walls, sizeof(Engine_Wall) * buffer);
    }
    if ((*walls) == NULL) {
        fprintf(stderr, "failed to create a wall...");
        exit(EXIT_FAILURE);
    }

    (*walls)[(*nb_walls)] = wall;
    (*nb_walls)++;
}

void generate_walls(Engine_Walls *walls, int *nb_walls) {
    assert(walls != NULL);
    assert(nb_walls != NULL);

    add_wall(walls, nb_walls, *init_wall(0, 0, OBJECT_DOWN, SIZE_Y));
    add_wall(walls, nb_walls, *init_wall(0, 0, OBJECT_RIGHT, SIZE_X));
    add_wall(walls, nb_walls, *init_wall(SIZE_X - 1, SIZE_Y, OBJECT_UP, SIZE_Y));
    add_wall(walls, nb_walls, *init_wall(SIZE_X, SIZE_Y - 1, OBJECT_LEFT, SIZE_X));

    add_wall(walls, nb_walls, *init_wall(0, 10, OBJECT_RIGHT, 30));
    add_wall(walls, nb_walls, *init_wall(10, 10, OBJECT_UP, 6));
    add_wall(walls, nb_walls, *init_wall(35, 0, OBJECT_DOWN, 35));
    add_wall(walls, nb_walls, *init_wall(35, 15, OBJECT_RIGHT, 20));
    add_wall(walls, nb_walls, *init_wall(45, 0, OBJECT_DOWN, 10));
    add_wall(walls, nb_walls, *init_wall(45, SIZE_Y, OBJECT_UP, 10));
    add_wall(walls, nb_walls, *init_wall(SIZE_X, 30, OBJECT_LEFT, 20));
    add_wall(walls, nb_walls, *init_wall(50, 30, OBJECT_UP, 10));
}

char *wall_to_string(Engine_Wall wall) {
    char *output;

    output = (char *)malloc(sizeof(char) * 64);

    sprintf(
        output,
        "%s, %s, %d",
        object_to_string(wall.obj),
        orientation_to_string(wall.orientation),
        wall.size);
    return output;
}

int wall_collision(Engine_Obj obj, Engine_Walls walls, int nb_walls) {
    int i;
    int *obj_coord, *wall_coord;

    assert(walls != NULL);

    obj_coord = get_object_coord(obj);

    for (i = 0; i < nb_walls; i++) {
        wall_coord = get_object_coord(walls[i].obj);


        /* on the same line ? horizontally */
        /* obj is between origine and limit of the wall ? Based on it's orientation. */
        if (
            obj_coord[0] == wall_coord[0]
            && walls[i].orientation == OBJECT_UP
            && obj_coord[1] < wall_coord[1]
            && obj_coord[1] >= wall_coord[1] - walls[i].size
        ) {
            free(obj_coord);
            free(wall_coord);
            return 1;
        } else if (
            obj_coord[0] == wall_coord[0]
            && walls[i].orientation == OBJECT_DOWN
            && obj_coord[1] >= wall_coord[1]
            && obj_coord[1] < wall_coord[1] + walls[i].size
        ) {
            free(obj_coord);
            free(wall_coord);
            return 1;
        } else if (
            obj_coord[1] == wall_coord[1]
            && walls[i].orientation == OBJECT_LEFT
            && obj_coord[0] < wall_coord[0]
            && obj_coord[0] >= wall_coord[0] - walls[i].size
        ) {
            free(obj_coord);
            free(wall_coord);
            return 1;
        } else if (
            obj_coord[1] == wall_coord[1]
            && walls[i].orientation == OBJECT_RIGHT
            && obj_coord[0] >= wall_coord[0]
            && obj_coord[0] < wall_coord[0] + walls[i].size
        ) {
            free(obj_coord);
            free(wall_coord);
            return 1;
        }

    }
    free(obj_coord);
    free(wall_coord);
    return 0;
}