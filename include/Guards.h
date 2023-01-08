#ifndef __GUARDS__
#define __GUARDS__

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "Config.h"
#include "Object.h"
#include "Wall.h"

typedef struct {
    Engine_Obj obj;
    Engine_Orientation direction;
    double speed;
} Engine_Guard;

Engine_Guard *init_guard(int x, int y);

/*Colision between gard and player, return 1 if player and guard are in same position, else 0;
 */
int detection(Engine_Obj guard, Engine_Obj player, Engine_Walls walls, int nb_walls);

Engine_Orientation guard_direction();

void move_guard(Engine_Guard *guard, Engine_Walls walls, int nb_walls);

#endif
