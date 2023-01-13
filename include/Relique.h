/**
 * @file Relique.h
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Manage all the interaction with the relics (header)
 * @version 0.1
 * @date 2023-01-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __RELIQUE__
#define __RELIQUE__

#include <assert.h>
#include <stdlib.h>

#include "Object.h"
#include "Player.h"
#include "Wall.h"

/**
 * @brief Relic's structure for the game, can be picked up by the player.
 *
 */
typedef struct {
    Engine_Obj obj;
    int is_picked_up;
} Engine_Relique;

/**
 * @brief initializes the relique to a position given in parameter
 *
 * @param x
 * @param y
 * @return Engine_Relique*
 */
Engine_Relique *init_relique(double x, double y);

/**
 * @brief fuction allowing the addition of relics
 *
 * @param tab
 * @param relique
 */
void add_Relique(Engine_Relique **tab, Engine_Relique relique);

/**
 * @brief generation of relics
 *
 * @param tab
 * @param walls
 * @param nb_walls
 */
void generate_relique(Engine_Relique **tab, Engine_Obj spawn, Engine_Walls walls, int nb_walls);

#endif