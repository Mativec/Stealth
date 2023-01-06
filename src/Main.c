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
    Engine_Input event;
    Engine_Obj object;
    int play;


    srand(time(NULL));

    quit = 0;
    nb_walls = 0;

    player = *init_object(5, 5);
    guard = *init_guard(25, 30);
    generate_walls(&walls, &nb_walls);

    /* Main loop over the frames... */
    while (play) {
        /*Some declaration of variables*/

        /*Get the time in nano second at the start of the frame */
        clock_gettime(CLOCK_REALTIME, &end_time);

        /* Display of the currentframe, samplefunction */
        /* THIS FUNCTION CALLS ONCE AND ONLY ONCE MLV_update_window */
        draw_window(player, guard.obj, walls, nb_walls); /* Graphisme.h */

        /* We get here some keyboard events*/
        event = get_event(); /* Input.h */

        /* Dealing with the events */
        
        play *= (event != INPUT_QUIT);

        /* Move the entities on the grid */
        move_player(&object, event);


        /* Collision detection and other game mechanisms */
        if (wall_collision(player, walls, nb_walls)) {
            move_object(&player, OBJECT_REVERT, 0);
        }

        move_guard(&guard, walls, nb_walls);

        if (detection(guard.obj, player)) {
            quit = 1;
        }

        /* Get the time in nano second at the end of the frame */
        clock_gettime(CLOCK_REALTIME, &new_time);

        refresh(end_time.tv_sec, new_time.tv_sec); /* Graphisme.h */
    }
    free_window();

    return 0;
}
