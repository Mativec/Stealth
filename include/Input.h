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

typedef enum __input{
    INPUT_NONE,
    INPUT_UP,
    INPUT_RIGHT,
    INPUT_LEFT,
    INPUT_DOWN,
    INPUT_QUIT
} Input;

Input get_event();

char *input_to_string(Input event);

#endif