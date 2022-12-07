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

#include "Input.h"

char* input_to_string(Input event) {
    switch (event) {
        case UP:
            return "UP";
        case LEFT:
            return "LEFT";
        case RIGHT:
            return "RIGHT";
        case DOWN:
            return "DOWN";
        case QUIT:
            return "QUIT";
        default:
            return "None";
    }
}

Input get_event() {
    MLV_Keyboard_button event;
    if(MLV_get_event(&event, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == MLV_KEY){
        switch(event){
            case MLV_KEYBOARD_UP : return UP;
            case MLV_KEYBOARD_LEFT : return LEFT;
            case MLV_KEYBOARD_RIGHT : return RIGHT;
            case MLV_KEYBOARD_DOWN : return DOWN;
            case MLV_KEYBOARD_q : return QUIT;
            default : return NONE;
        }
    }
    return NONE;
}