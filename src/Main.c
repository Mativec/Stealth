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
    int i;
    int quit, nb_walls, nb_guards, nb_reliques, nb_reliques_claims;
    char *player_name;
    struct timespec end_time, new_time;

    Engine_Input event;
    Engine_Player player;
    Engine_Guard *guards;
    Engine_Walls walls;
    Engine_Obj base_player;
    Engine_Relique *reliques;

    player_name = "Player";
    quit = 0;
    nb_walls = 0;
    nb_guards = 0;
    nb_reliques = 0;
    nb_reliques_claims = 0;

    srand(time(NULL));

    player = *init_player(BASE_PLAYER_X, BASE_PLAYER_Y);
    base_player = *init_object(player.obj.x, player.obj.y);
    
    generate_walls(&walls, &nb_walls);
    generate_guards(&guards, &nb_guards);
    genere_relique(&reliques, &nb_reliques, walls, nb_walls);
    add_wall(&walls, &nb_walls, *init_wall(31, 10, OBJECT_DOWN, 32));
    add_wall(&walls, &nb_walls, *init_wall(30, 42, OBJECT_RIGHT, 30));

    /* Main loop over the frames... */
    while (!quit) {

        /*Get the time in nano second at the start of the frame */
        clock_gettime(CLOCK_REALTIME, &end_time);

        /* Display of the currentframe, samplefunction */
        /* THIS FUNCTION CALLS ONCE AND ONLY ONCE MLV_update_window */
        draw_window(base_player, player, guards, nb_guards, walls, nb_walls, reliques, nb_reliques); /* Graphisme.h */

        /* We get here some keyboard events*/
        event = get_event(&(player.power_one), &(player.power_two));

        /* Dealing with the events */
        quit = (event == INPUT_QUIT);

        /* Move the entities on the grid */
        move_player(&player, event);

        /* Collision detection and other game mechanisms */
        if (wall_collision(player.obj, walls, nb_walls)) {
            move_object(&(player.obj), OBJECT_REVERT, 0);
        }

        for(i = 0; i < nb_reliques; i++){
            /* If the relique aren't claimed and on the same position of the player */
            if(!(reliques[i].is_picked_up) && contact_between_objects(player.obj, reliques[i].obj)){
                reliques[i].is_picked_up = 1;
                nb_reliques_claims++;
            }
        }
        if(nb_reliques_claims == nb_reliques && contact_between_objects(player.obj, base_player)){
            quit = 2;
        }

        for (i = 0; i < nb_guards; i++){
            /* move_guard(&(guards[i]), walls, nb_walls); */
            if (detection(guards[i], player.obj, walls, nb_walls)) {
                quit = 1;
            }
        }

        /* Get the time in nano second at the end of the frame */
        clock_gettime(CLOCK_REALTIME, &new_time);

        refresh(end_time.tv_sec, new_time.tv_sec); /* Graphisme.h */
    }

    if(quit == 2){
        printf("Victoire\n");
    }

    MLV_wait_milliseconds(1000);
    fprintf(stderr, "%s\n", player_to_string(player, player_name));
    
    MLV_free_window();
    return 0;
}
