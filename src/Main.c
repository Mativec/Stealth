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
    Engine_Guard guard;
    Engine_Walls walls;
    Engine_Obj base_player;
    Engine_Relique *reliques;

    int quit, nb_walls, nb_reliques, nb_reliques_claims;

    /*pour move gard a deplacer */
    int i;
    char *player_name;
    srand( time(NULL));

    player_name = "Player";
    quit = 0;
    nb_walls = 0;
    nb_reliques = 0;
    nb_reliques_claims = 0;


    player = *init_player(BASE_PLAYER_X, BASE_PLAYER_Y);
    base_player = *init_object(player.obj.x, player.obj.y);

    guard = *init_guard(25, 30);
    
    generate_walls(&walls, &nb_walls);
    genere_relique(&reliques, &nb_reliques, walls, nb_walls);


    /* Main loop over the frames... */
    while (!quit) {

        /*Get the time in nano second at the start of the frame */
        clock_gettime(CLOCK_REALTIME, &end_time);

        /* Display of the currentframe, samplefunction */
        /* THIS FUNCTION CALLS ONCE AND ONLY ONCE MLV_update_window */
        draw_window(base_player, player, guard.obj, walls, nb_walls, reliques, nb_reliques); /* Graphisme.h */

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

        move_guard(&guard, walls, nb_walls);

        /*mettre le if 3 reliques sont picked up et que le joueur atteint la pos initial c gagné
        */
        for(i = 0; i < nb_reliques; i++){
            if(!(reliques[i].is_picked_up) && distance_between_objects(player.obj, reliques[i].obj) == 0){
                reliques[i].is_picked_up++;
                nb_reliques_claims++;
            }
        }

        if(nb_reliques_claims == nb_reliques && distance_between_objects(player.obj, base_player) == 0){
            quit = 2;
        }

        if (detection(guard.obj, player.obj)) {
            quit = 1;
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
