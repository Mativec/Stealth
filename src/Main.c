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
    Engine_Obj player;
    Engine_Guard guard;
    Engine_Walls walls;
    /*tableau de reliques*/
    Engine_Relique *reliques;
    int quit, nb_walls, nb_reliques;

    int i;

    quit = 0;
    nb_walls = 0;
    nb_reliques = 0;

    player = *init_object(5, 5);
    guard = *init_guard(25, 30);
    generate_walls(&walls, &nb_walls);
    add_Relique(&reliques, &nb_reliques, *init_reliques(20, 20));
    /* Main loop over the frames... */
    while (!quit) {
        /*Some declaration of variables*/

        /*Get the time in nano second at the start of the frame */
        clock_gettime(CLOCK_REALTIME, &end_time);

        /* Display of the currentframe, samplefunction */
        /* THIS FUNCTION CALLS ONCE AND ONLY ONCE MLV_update_window */
        draw_window(player, *(guard.obj), walls, nb_walls, reliques, nb_reliques); /* Graphisme.h */

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
        move_player(&player, event);

        /* Collision detection and other game mechanisms */
        if (wall_collision(player, walls, nb_walls)) {
            move_object(&player, OBJECT_REVERT);
        }

        move_guard(&guard, walls, nb_walls);
        for(i = 0; i < nb_reliques; i++){
            printf("%s  %s\n", object_to_string(player), object_to_string(reliques[i].obj));
            if(distance_between_objects(player, reliques[i].obj) == 0){
                reliques[i].is_picked_up = 1;
            }
        }

        if(detection(*(guard.obj), player)){
            quit = 1;
        }

        /* Get the time in nano second at the end of the frame */
        clock_gettime(CLOCK_REALTIME, &new_time);

        refresh(end_time.tv_sec, new_time.tv_sec); /* Graphisme.h */
    }
    MLV_wait_milliseconds(1000);
    free_walls(walls, &nb_walls);
    free_window();

    return 0;
}
