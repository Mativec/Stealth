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

#include "Graphisme.h"
#include "Input.h"

int main(int argc, char* argv[]) {
    int quit;
    struct timespec end_time, new_time;
    Input event;

    quit = 0;
    
    /* Main loop over the frames... */
    while (!quit) {
        /*Some declaration of variables*/

        /*Get the time in nano second at the start of the frame */
        clock_gettime(CLOCK_REALTIME, &end_time);

        /* Display of the currentframe, samplefunction */
        /* THIS FUNCTION CALLS ONCE AND ONLY ONCE MLV_update_window */
        draw_window(); /* Graphisme.h */

        /* We get here some keyboard events*/
        event = get_event(); /* Input.h */

        /* Dealing with the events */
        if(event != NONE){
            printf("%s\n", input_to_string(event));
        }
        
        quit = (event == QUIT);

        /* Move the entities on the grid */

        /* Collision detection and other game mechanisms */

        /* Get the time in nano second at the end of the frame */
        clock_gettime(CLOCK_REALTIME, &new_time);

        refresh(end_time.tv_sec, new_time.tv_sec); /* Graphisme.h */
    }
    free_window();

    return 0;
}
