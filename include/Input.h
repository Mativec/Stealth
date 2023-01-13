/**
 * @file Input.h
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Manage all the interaction with the player (header)
 * @version 0.1
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __INPUT
#define __INPUT

#include <MLV/MLV_event.h>
#include <assert.h>

#include "Object.h"

/**
 * @brief Represent the input of thee player to interact with the game
 * skills are manage in the get_event function.
 *
 */
typedef enum {
    INPUT_NONE,
    INPUT_UP,    /* want to move to the  up */
    INPUT_RIGHT, /* want move to the right */
    INPUT_LEFT,  /* want to move to the left */
    INPUT_DOWN,  /* want to move to the down */
    INPUT_QUIT   /* want to quit the game */
} Engine_Input;

/**
 * @brief Get the event object
 *
 * @param power_one
 * @param power_two
 * @return Engine_Input
 */
Engine_Input get_event(int *power_one, int *power_two);

/**
 * @brief return orientation of the Object input
 *
 * @param input
 * @return Engine_Orientation
 */
Engine_Orientation input_to_orientation(Engine_Input input);

/**
 * @brief return the orientation in string
 *
 * @param event
 * @return char*
 */
char *input_to_string(Engine_Input event);

#endif
