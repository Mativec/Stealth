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



/**
 * @brief initializes the guard to a position given in parameter
 * 
 * @param x 
 * @param y 
 * @return Engine_Guard* 
 */
Engine_Guard *init_guard(int x, int y);



/**
 * @brief Tell if the target is on the field of view of the guard.
 * 
 * @param guard 
 * @param target 
 * @param panic_mode 
 * @return int 
 */
int in_fov_guard(Engine_Guard guard, Engine_Obj target, int panic_mode);


/**
 * @brief  detection between guard and player and uses the field of view of the guard 
 * 
 * @param guard 
 * @param player 
 * @param panic_mode 
 * @param walls 
 * @param nb_walls 
 * @return int 
 */
int detection(Engine_Guard guard, Engine_Obj player, int panic_mode, Engine_Walls walls, int nb_walls);


/**
 * @brief allows the direction of the guard
 * 
 * @return Engine_Orientation 
 */
Engine_Orientation guard_direction();


/**
 * @brief  movement of the guard
 * 
 * @param guard 
 * @param panic_mode 
 * @param walls 
 * @param nb_walls 
 */
void move_guard(Engine_Guard *guard, int panic_mode, Engine_Walls walls, int nb_walls);


/**
 * @brief generation of the number of guards
 * 
 * @param guards 
 */
void generate_guards(Engine_Guard ** guards, Engine_Obj spawn, Engine_Walls walls, int nb_walls);

#endif
