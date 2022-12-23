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
#include <stdlib.h>

#include "Config.h"
#include "Object.h"

typedef struct _wall {
    Engine_Obj coord;
    Engine_Orientation orientation;
    int size;
} Wall, *Walls;

Wall *init_wall(float x, float y, Engine_Orientation way, int size);

void add_wall(Walls *walls, int *nb_wall, Wall wall);

Walls generate_walls(int nb_walls);

void wall_collision(Engine_Obj *obj);

#endif