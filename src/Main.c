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
    Engine_Walls walls;
    int quit, nb_walls;

    quit = 0;
    nb_walls = 0;
    walls = NULL;

    player = *init_object(30, 20);

    add_wall(&walls, &nb_walls, *init_wall(0, 0, OBJECT_DOWN, SIZE_Y));
    add_wall(&walls, &nb_walls, *init_wall(0, 0, OBJECT_RIGHT, SIZE_X));
    add_wall(&walls, &nb_walls, *init_wall(SIZE_X - 1, SIZE_Y, OBJECT_UP, SIZE_Y));
    add_wall(&walls, &nb_walls, *init_wall(SIZE_X, SIZE_Y - 1, OBJECT_LEFT, SIZE_X));
    add_wall(&walls, &nb_walls, *init_wall(30, 30, OBJECT_RIGHT, 5));

    /* Main loop over the frames... */
    while (!quit) {
        /*Some declaration of variables*/

        /*Get the time in nano second at the start of the frame */
        clock_gettime(CLOCK_REALTIME, &end_time);

        /* Display of the currentframe, samplefunction */
        /* THIS FUNCTION CALLS ONCE AND ONLY ONCE MLV_update_window */
        draw_window(player, walls, nb_walls); /* Graphisme.h */

        /* We get here some keyboard events*/
        event = get_event(); /* Input.h */

        /* Dealing with the events */

        quit = (event == INPUT_QUIT);

        /* Move the entities on the grid */
        move_player(&player, event);

        /* Collision detection and other game mechanisms */
        if(wall_collision(player, walls, nb_walls)){
            move_object(&player, OBJECT_REVERT);
        }

        /* Get the time in nano second at the end of the frame */
        clock_gettime(CLOCK_REALTIME, &new_time);

        refresh(end_time.tv_sec, new_time.tv_sec); /* Graphisme.h */
    }
    free_window();
    free_walls(walls, &nb_walls);

    return 0;
}
