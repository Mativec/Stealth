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

    int quit, nb_walls;
    int mana_cost;
    char *player_name;


    srand(time(NULL));

    player_name = "Player";
    quit = 0;
    nb_walls = 0;

    player = *init_player(5, 5);
    guard = *init_guard(25, 30);
    generate_walls(&walls, &nb_walls);

    /* Main loop over the frames... */
    do {
        /*Some declaration of variables*/

        /*Get the time in nano second at the start of the frame */
        clock_gettime(CLOCK_REALTIME, &end_time);

        /* Display of the currentframe, samplefunction */
        /* THIS FUNCTION CALLS ONCE AND ONLY ONCE MLV_update_window */
        draw_window(player, guard.obj, walls, nb_walls); /* Graphisme.h */

        /* We get here some keyboard events*/
        event = get_event(&(player.overcharge), &(player.invisibility));

        /* Dealing with the events */
        
        mana_cost = (player.overcharge * MANA_PER_TUILE) +  (player.invisibility * MANA_PER_TUILE);

        if(player.mana >= mana_cost){
            player.mana -= mana_cost;
        }else{
            player.invisibility = 0;
            player.overcharge = 0;
        }

        quit = (event == INPUT_QUIT);

        /* Move the entities on the grid */
        move_player(&player, event);

        /* Collision detection and other game mechanisms */
        if (wall_collision(player.obj, walls, nb_walls)) {
            move_object(&(player.obj), OBJECT_REVERT, 0);
        }

        move_guard(&guard, walls, nb_walls);

        /* His seen by a guardian and didn't activate the invisibility */
        if (detection(guard.obj, player.obj) && !player.invisibility) {
            quit = 1;
        }

        /* TODO : Mana on tuile */
        player.mana ++;
        if(player.mana > MAX_MANA){
            player.mana = MAX_MANA;
        }

        /* Get the time in nano second at the end of the frame */
        clock_gettime(CLOCK_REALTIME, &new_time);

        refresh(end_time.tv_sec, new_time.tv_sec); /* Graphisme.h */
    } while (!quit);
    
    MLV_wait_milliseconds(1000);
    fprintf(stderr, "%s\n", player_to_string(player, player_name));
    free_walls(walls, &nb_walls);
    free_window();

    return 0;
}
