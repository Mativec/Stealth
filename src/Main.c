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
    Engine_Player player;
    Engine_Guard *guards;
    Engine_Walls walls;

    int quit;
    int nb_walls, nb_guards;
    int i;
    char *player_name;


    srand(time(NULL));

    player_name = "Player";
    quit = 0;
    nb_walls = 0;

    player = *init_player(5, 5);

    generate_walls(&walls, &nb_walls);
    generate_guards(&guards, &nb_guards);

    /* Main loop over the frames... */
    while (!quit) {
        /*Some declaration of variables*/

        /*Get the time in nano second at the start of the frame */
        clock_gettime(CLOCK_REALTIME, &end_time);

        /* Display of the currentframe, samplefunction */
        /* THIS FUNCTION CALLS ONCE AND ONLY ONCE MLV_update_window */
        draw_window(player, guards, nb_guards, walls, nb_walls); /* Graphisme.h */

        /* We get here some keyboard events*/
        event = get_event(&(player.power_one), &(player.power_two));

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
        if (wall_collision(player.obj, walls, nb_walls)) {
            move_object(&(player.obj), OBJECT_REVERT, 0);
        }

        for (i = 0; i < nb_guards; i++){
            move_guard(&(guards[i]), walls, nb_walls);

            if (detection(guards[i].obj, player.obj)) {
                quit = 1;
            }
        }

        /* Get the time in nano second at the end of the frame */
        clock_gettime(CLOCK_REALTIME, &new_time);

        refresh(end_time.tv_sec, new_time.tv_sec); /* Graphisme.h */
    }
    MLV_wait_milliseconds(1000);
    fprintf(stderr, "%s\n", player_to_string(player, player_name));
    free_walls(walls, &nb_walls);
    free_window();

    return 0;
}
