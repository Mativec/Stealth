/**
 * @file Input.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../include/Input.h"

char* input_to_string(Engine_Input event) {
    switch (event) {
        case INPUT_UP:
            return "UP";
        case INPUT_LEFT:
            return "LEFT";
        case INPUT_RIGHT:
            return "RIGHT";
        case INPUT_DOWN:
            return "DOWN";
        case INPUT_QUIT:
            return "QUIT";
        default:
            return "None";
    }
}

Engine_Orientation input_to_orientation(Engine_Input input){
    switch(input){
        case INPUT_UP:
            return OBJECT_UP;
        case INPUT_LEFT:
            return OBJECT_LEFT;
        case INPUT_RIGHT:
            return OBJECT_RIGHT;
        case INPUT_DOWN:
            return OBJECT_DOWN;
        default:
            return OBJECT_NONE;
    }
}

Engine_Input get_event(int *power_one,  int *power_two) {
    static int noTwice = 0;
    Engine_Input input;

    input = INPUT_NONE;

    if(noTwice){
        noTwice = 0;
    }
    else{
        noTwice = 1;
        if(MLV_get_keyboard_state(MOVE_UP) == MLV_PRESSED){
            input = INPUT_UP;
        }
        else if(MLV_get_keyboard_state(MOVE_LEFT) == MLV_PRESSED){
            input = INPUT_LEFT;
        }
        else if(MLV_get_keyboard_state(MOVE_RIGHT) == MLV_PRESSED){
            input = INPUT_RIGHT;
        }
        else if(MLV_get_keyboard_state(MOVE_DOWN) == MLV_PRESSED){
            input = INPUT_DOWN;
        }
        else if(MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED){
            input = INPUT_QUIT;
        }
    }
    
    return input;
}
