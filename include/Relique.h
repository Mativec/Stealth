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



Engine_Relique *init_relique(double x, double y);

void add_Relique(Engine_Relique** tab, int* nb_reliques, Engine_Relique relique);

void genere_relique(Engine_Relique **tab, int *nb_reliques, Engine_Walls walls, int nb_walls);

void test_coord_reliques_joueurs(Engine_Relique *reliques, Engine_Player player, int nb_reliques);
#endif