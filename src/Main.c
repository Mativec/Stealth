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
    Engine_Obj player;
    Walls walls;
    int quit, nb_wall;

    quit = 0;
    nb_wall = 0;
    walls = NULL;

    player = *init_object(30, 20);

    add_wall(&walls, &nb_wall, *init_wall(0, 0, OBJECT_DOWN, SIZE_Y));
    add_wall(&walls, &nb_wall, *init_wall(0, 0, OBJECT_RIGHT, SIZE_X));
    add_wall(&walls, &nb_wall, *init_wall(SIZE_X - 1, SIZE_Y, OBJECT_UP, SIZE_Y));
    add_wall(&walls, &nb_wall, *init_wall(SIZE_X, SIZE_Y - 1, OBJECT_LEFT, SIZE_X));

    /* Main loop over the frames... */
    while (!quit) {
        /*Some declaration of variables*/

        /*Get the time in nano second at the start of the frame */
        clock_gettime(CLOCK_REALTIME, &end_time);

        /* Display of the currentframe, samplefunction */
        /* THIS FUNCTION CALLS ONCE AND ONLY ONCE MLV_update_window */
        draw_window(player, walls, nb_wall); /* Graphisme.h */

        /* We get here some keyboard events*/
        event = get_event(); /* Input.h */

        /* Dealing with the events */
        if (event != INPUT_NONE) {
            /*
            printf("%s\n", input_to_string(event));
            printf("%s\n", object_to_string(player));
            */
        }

        quit = (event == INPUT_QUIT);

        /* Move the entities on the grid */
        move_player(&player, event);

        /* Collision detection and other game mechanisms */
        wall_collision(&player);

        /* Get the time in nano second at the end of the frame */
        clock_gettime(CLOCK_REALTIME, &new_time);

        refresh(end_time.tv_sec, new_time.tv_sec); /* Graphisme.h */
    }
    free_window();

    return 0;
}
