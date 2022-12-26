/**
 * @file Main.c
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Main du projet
 * @version 0.1
 * @date 2022-11-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#define _POSIX_C_SOURCE 199309L

#include <time.h>

#include "../include/all.h"

int main(int argc, char* argv[]) {
    struct timespec end_time, new_time;
    Input event;
    Engine_Obj object;
    int quit;

    quit = 0;
    object = *init_object(500, 500, SPEED_PLAYER);

    title_screen();

    /* Main loop over the frames... */
    while (!quit) {
        /*Some declaration of variables*/

        /*Get the time in nano second at the start of the frame */
        clock_gettime(CLOCK_REALTIME, &end_time);

        /* Display of the currentframe, samplefunction */
        /* THIS FUNCTION CALLS ONCE AND ONLY ONCE MLV_update_window */
        draw_window(object); /* Graphisme.h */

        /* We get here some keyboard events*/
        event = get_event(); /* Input.h */

        /* Dealing with the events */
        if (event != INPUT_NONE) {
            /*
            printf("%s\n", input_to_string(event));
            */
        }
        
        quit = (event == INPUT_QUIT);

        /* Move the entities on the grid */
        move_player(&object, event);


        /* Collision detection and other game mechanisms */
        if (object.x < 0 || object.x > SIZE_X || object.y < 0 || object.y > SIZE_Y) {
            move_object(&object, OBJECT_REVERT);
        }

        /* Get the time in nano second at the end of the frame */
        clock_gettime(CLOCK_REALTIME, &new_time);

        refresh(end_time.tv_sec, new_time.tv_sec); /* Graphisme.h */
    }
    free_window();

    return 0;
}
