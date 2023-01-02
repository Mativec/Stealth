/**
 * @file Wall.h
 * @author VECCHIO Matias & ARNAOUT Richard
 * @brief Module de gestion des murs du jeu.
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __WALL__
#define __WALL__

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "Config.h"
#include "Object.h"

typedef struct _wall {
    Engine_Obj obj;
    Engine_Orientation orientation;
    int size;
} Engine_Wall, *Engine_Walls;

Engine_Wall *init_wall(float x, float y, Engine_Orientation way, int size);

void add_wall(Engine_Walls *walls, int *nb_wall, Engine_Wall wall);

void generate_walls(Engine_Walls *walls, int *nb_walls);

char *orientation_to_string(Engine_Orientation orientation);

char *wall_to_string(Engine_Wall wall);

int wall_collision(Engine_Obj obj, Engine_Walls walls, int nb_walls);

void free_walls(Engine_Walls walls, int *nb_walls);

#endif