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

char *input_to_string(Engine_Input event) {
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

Engine_Orientation input_to_orientation(Engine_Input input) {
    switch (input) {
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

Engine_Input get_event(int *power_one, int *power_two) {
    static int noTwice = 0;
    MLV_Keyboard_modifier button_mod;
    Engine_Input output;

    output = INPUT_NONE;

    if(noTwice){
        noTwice = 0;
    }
    else{
        noTwice = 1;
        
        MLV_get_event(NULL, &button_mod, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

        if (power_one != NULL) {
            *power_one = MLV_shift_key_was_pressed(button_mod);
        }

        if (MLV_get_keyboard_state(MOVE_UP) == MLV_PRESSED) {
            output = INPUT_UP;
        } else if (MLV_get_keyboard_state(MOVE_LEFT) == MLV_PRESSED) {
            output = INPUT_LEFT;
        } else if (MLV_get_keyboard_state(MOVE_RIGHT) == MLV_PRESSED) {
            output = INPUT_RIGHT;
        } else if (MLV_get_keyboard_state(MOVE_DOWN) == MLV_PRESSED) {
            output = INPUT_DOWN;
        } else if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED) {
            output = INPUT_QUIT;
        }
        if (power_two != NULL && MLV_get_keyboard_state(MLV_KEYBOARD_SPACE)) {
            *power_two = 1 - *power_two;
        }
    }
    return output;
}
