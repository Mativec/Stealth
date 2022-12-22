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

Wall * init_wall(float x, float y, Engine_Orientation way, int size) {
    Wall *new_wall;

    new_wall = (Wall *)malloc(sizeof(Wall));

    if (new_wall != NULL) {
        new_wall->coord = *init_object(x, y);
        new_wall->orientation = way;
        new_wall->size = size;
    }
    return new_wall;
}

void add_wall(Walls * walls, int * nb_wall, Wall wall){
    static int buffer = 0;

    assert(walls);
    assert(nb_wall);

    while((*nb_wall) < buffer){
        buffer *= 2;
        *walls = realloc(*walls, buffer);
    }
    (*walls)[*nb_wall] = wall;
    (*nb_wall)++;
    printf("nb_wall : %d (%f, %f, %d)\n", *nb_wall, wall.coord.x, wall.coord.y, wall.size);
}

Walls generate_walls(int nb_walls) {
    return NULL;
}