/**
 * @file Input.h
 * @author your name (you@domain.com)
 * @brief 
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

typedef enum __input{
    INPUT_NONE,
    INPUT_UP,
    INPUT_RIGHT,
    INPUT_LEFT,
    INPUT_DOWN,
    INPUT_QUIT
} Engine_Input;


/**
 * @brief Get the event object
 * 
 * @param power_one 
 * @param power_two 
 * @return Engine_Input 
 */
Engine_Input get_event(int *power_one,  int *power_two);



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
