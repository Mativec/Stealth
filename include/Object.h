/**
 * @file Object.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __OBJECT
#define __OBJECT

#include <stdlib.h>
#include <stdio.h>

typedef struct engine_object{
    float x;
    float y;
    int speed;
} Engine_Obj;

typedef enum {
    OBJECT_NONE,
    OBJECT_UP,
    OBJECT_LEFT,
    OBJECT_RIGHT,
    OBJECT_DOWN,
    OBJECT_REVERT
} Engine_Orientation;


/**
 * @brief Initiate a new Object.
 * 
 * @param x : x coordinate.
 * @param y : y coordinate.
 * @param speed : speed of the object (0 -> don't move).
 * @return Engine_Obj* a pointer to the new object.
 */
Engine_Obj *init_object(float x, float y, int speed);


/**
 * @brief move an object base on it's speed.
 * 
 * @param obj : object to move
 * @param way : way to move obj
 */
void move_object(Engine_Obj *obj, Engine_Orientation way);


/**
 * @brief Return a string version of an object.
 * 
 * @param obj : object to transform.
 * @return char* : string version.
 */
char *object_to_string(Engine_Obj obj);

#endif
