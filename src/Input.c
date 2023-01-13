/**
 * @file Input.c
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Manage all the interaction with the player (source)
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
    MLV_Button_state button_state;
    MLV_Keyboard_button button;
    Engine_Input output;

    output = INPUT_NONE;

    if (noTwice) {
        noTwice = 0;
    } else {
        noTwice = 1;

        MLV_get_event(&button, &button_mod, NULL, NULL, NULL, NULL, NULL, NULL, &button_state);

        if (power_one != NULL) {
            *power_one =
                MLV_get_keyboard_state(MLV_KEYBOARD_LSHIFT) == MLV_PRESSED ||
                MLV_get_keyboard_state(MLV_KEYBOARD_RSHIFT) == MLV_PRESSED;
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
        if (power_two != NULL) {
            if (button == MLV_KEYBOARD_SPACE && button_state == MLV_PRESSED) {
                *power_two = 1 - *power_two;
            }
        }
    }
    return output;
}
