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

int in_fov_guard(Engine_Guard guard, Engine_Obj target);

int detection(Engine_Guard guard, Engine_Obj player, Engine_Walls walls, int nb_walls);

Engine_Orientation guard_direction();

void move_guard(Engine_Guard *guard, Engine_Walls walls, int nb_walls);

void generate_guards(Engine_Guard ** guards, int *nb_guards);

#endif
