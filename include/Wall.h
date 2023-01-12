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


/**
 * @brief Wall's structure for the game
 * Walls represent an array of Wall.
 * 
 */
typedef struct _wall {
    Engine_Obj obj;
    Engine_Orientation orientation;
    int size;
} Engine_Wall, *Engine_Walls;


/**
 * @brief Init an Engine_Wall instance.
 * 
 * @param x : x base point coordinate.
 * @param y ; y base point coordinate.
 * @param way : orientation of the wall
 * @param size : width of the wall (from the base).
 * @return Engine_Wall* a pointer to a Wall.
 */
Engine_Wall *init_wall(int x, int y, Engine_Orientation way, int size);


/**
 * @brief Add a wall to an array of wall (Engine_Walls).
 * 
 * @param walls : a pointer to an array of Engine_Wall .
 * @param nb_walls : a pointer to the size of walls .
 * @param wall : a wall to add on walls .
 */
void add_wall(Engine_Walls *walls, int *nb_walls, Engine_Wall wall);

void generate_border(Engine_Walls *walls, int *nb_walls);

/**
 * @brief generate all the walls for the game and stock them on walls.
 * 
 * @param walls : a pointer to an array of Engine_Wall .
 * @param nb_walls : a pointer to the size of walls .
 */
void generate_walls(Engine_Walls *walls, int *nb_walls, int x, int y);


/**
 * @brief Return a char* equivalent of an instance of Engine_Wall
 * 
 * @param wall : an Engine_Wall's instance.
 * @return char* : it's string equivalent.
 */
char *wall_to_string(Engine_Wall wall);


/**
 * @brief Return 1 if there is a collision between obj and a wall in walls.
 * 
 * @param obj : the object to inspect.
 * @param walls : an array of Engine_Wall.
 * @param nb_walls : the size of walls.
 * @return int : 1 if there is a collision, 0 either.
 */
int wall_collision(Engine_Obj obj, Engine_Walls walls, int nb_walls);

/**
 * @brief Free an array of engine_Wall and reset it's size.
 * 
 * @param walls : an array of Engine_Wall.
 * @param nb_walls : the size of walls.
 */
void free_walls(Engine_Walls walls, int *nb_walls);

#endif