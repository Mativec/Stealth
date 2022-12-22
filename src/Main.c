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
    Walls walls;
    int quit, nb_wall;

    quit = 0;
    nb_wall = 0;

    object = *init_object(30, 20);

    printf("Walls init\n");
    walls = (Walls) malloc(sizeof(Wall));
    add_wall(&walls, &nb_wall, *init_wall(0, 0, OBJECT_DOWN, SIZE_Y));
    add_wall(&walls, &nb_wall, *init_wall(0, 0, OBJECT_RIGHT, SIZE_X));
    add_wall(&walls, &nb_wall, *init_wall(SIZE_X, SIZE_Y, OBJECT_UP, SIZE_Y));
    add_wall(&walls, &nb_wall, *init_wall(SIZE_X,SIZE_Y, OBJECT_LEFT, SIZE_X));

    /* Main loop over the frames... */
    while (!quit) {
        /*Some declaration of variables*/

        /*Get the time in nano second at the start of the frame */
        clock_gettime(CLOCK_REALTIME, &end_time);

        /* Display of the currentframe, samplefunction */
        /* THIS FUNCTION CALLS ONCE AND ONLY ONCE MLV_update_window */
        draw_window(object, walls, 2); /* Graphisme.h */

        /* We get here some keyboard events*/
        event = get_event(); /* Input.h */

        /* Dealing with the events */
        if (event != INPUT_NONE) {
            printf("%s\n", input_to_string(event));
            printf("%s\n", object_to_string(object));
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
