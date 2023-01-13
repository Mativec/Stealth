#ifndef __RELIQUE__
#define __RELIQUE__

#include <assert.h>
#include <stdlib.h>
#include "Object.h"
#include "Player.h"
#include "Wall.h"

typedef struct{
    Engine_Obj obj;
    int is_picked_up;
}Engine_Relique;


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
 * @param nb_reliques 
 * @param relique 
 */
void add_Relique(Engine_Relique** tab, int* nb_reliques, Engine_Relique relique);



/**
 * @brief generation of relics
 * 
 * @param tab 
 * @param nb_reliques 
 * @param walls 
 * @param nb_walls 
 */
void genere_relique(Engine_Relique **tab, int *nb_reliques, Engine_Walls walls, int nb_walls);



/**
 * @brief function allowing test to see coordonates of relics and the player
 * 
 * @param reliques 
 * @param player 
 * @param nb_reliques 
 */
void test_coord_reliques_joueurs(Engine_Relique *reliques, Engine_Player player, int nb_reliques);
#endif