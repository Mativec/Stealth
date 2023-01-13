/**
 * @file Object.h
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Base management for all game objects (header)
 * @version 0.1
 * @date 2022-12-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __OBJECT
#define __OBJECT

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Config.h"

/**
 * @brief Base object for the game
 *
 */
typedef struct {
    double x;
    double y;
} Engine_Obj;

/**
 * @brief Orientation used for movement / object in general
 *
 */
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
 * @return Engine_Obj* a pointer to the new object.
 */
Engine_Obj *init_object(double x, double y);

/**
 * @brief move an object base on it's speed.
 *
 * @param obj : object to move
 * @param way : way to move obj
 */
void move_object(Engine_Obj *obj, Engine_Orientation way, double factor);

/**
 * @brief Return a string version of an object.
 *
 * @param obj : object to transform.
 * @return char* : string version.
 */
char *object_to_string(Engine_Obj obj);

/**
 * @brief Get obj's cooridinate.
 *
 * @param obj : the Engine_Object which we want the coordinate
 * @return int* : an array of two integers ([x][y])
 */
void get_object_coord(Engine_Obj obj, int coords[2]);

/**
 * @brief Return the distance between 2 objects.
 *
 * @param obj1
 * @param obj2
 * @return double
 */
int distance_between_objects(Engine_Obj obj1, Engine_Obj obj2);

/**
 * @brief return the result of contact between 2 objects who are in the same place
 *
 * @param obj1
 * @param obj2
 * @return int
 */
int contact_between_objects(Engine_Obj obj1, Engine_Obj obj2);

/**
 * @brief Return a char* equivalent of the enum Engine_Orientation.
 *
 * @param orientation : an Engine_Orientation's instance.
 * @return char* : it's string equivalent.
 */
char *orientation_to_string(Engine_Orientation orientation);

#endif
