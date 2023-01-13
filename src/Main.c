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
    int i, j, time_game;
    int quit, nb_walls, nb_guards, nb_reliques, nb_reliques_claims;
    int mana_cost, panic_mode, has_panic_mode;
    struct timespec end_time, new_time, begin_time, panic_time;

    MLV_Image *image;
    MLV_Music *music;
    Engine_Input event;
    Engine_Player player;
    Engine_Guard *guards;
    Engine_Walls walls;
    Engine_Obj base_player;
    Engine_Relique *reliques;


    quit = 0;
    nb_walls = 0;
    nb_guards = 0;
    nb_reliques = 0;
    nb_reliques_claims = 0;
    has_panic_mode = 0;
    panic_mode = 0;
    image = NULL;
    music = NULL;

    srand(time(NULL));

    player = *init_player(BASE_PLAYER_X, BASE_PLAYER_Y);
    base_player = *init_object(player.obj.x, player.obj.y);
    
    generate_walls(&walls, &nb_walls);
    generate_guards(&guards, &nb_guards);
    genere_relique(&reliques, &nb_reliques, walls, nb_walls);


    if(title_screen(image) == 1){
        quit = 1;
    }

    if(quit != 1){
        play_sound(music);
    }

    clock_gettime(CLOCK_REALTIME, &begin_time);
    /* Main loop over the frames... */
    while (!quit){

        /*Get the time in nano second at the start of the frame */
        clock_gettime(CLOCK_REALTIME, &end_time);

        /* Display of the currentframe, samplefunction */
        /* THIS FUNCTION CALLS ONCE AND ONLY ONCE MLV_update_window */
        draw_window(base_player, player, guards, nb_guards, panic_mode, walls, nb_walls, reliques, nb_reliques); /* Graphisme.h */

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

        for(i = 0; i < nb_reliques; i++){
            /* If the relique aren't claimed and on the same position of the player */
            if(!(reliques[i].is_picked_up) && contact_between_objects(player.obj, reliques[i].obj)){
                reliques[i].is_picked_up = 1;
                nb_reliques_claims++;
            }
            if(!panic_mode && !has_panic_mode){
                for (j = 0; j < nb_guards; j++){
                    if(reliques[i].is_picked_up && detection(guards[j], reliques[i].obj, panic_mode, walls, nb_walls)){
                        has_panic_mode = 1;
                        panic_mode = 1;
                        clock_gettime(CLOCK_REALTIME, &panic_time);
                    }
                }
            }
        }
        if(nb_reliques_claims == nb_reliques && contact_between_objects(player.obj, base_player)){
            quit = 2;
        }

        /* His seen by a guardian and didn't activate the invisibility */
        for (i = 0; i < nb_guards; i++){
            move_guard(&(guards[i]), panic_mode, walls, nb_walls);
            if (detection(guards[i], player.obj, panic_mode, walls, nb_walls) && !player.invisibility) {
                quit = 3;
            }
        }
        /* TODO : Mana on tuile */
        if(player.mana > MAX_MANA){
            player.mana = MAX_MANA;
        }

        if(panic_mode){
            if(new_time.tv_sec - panic_time.tv_sec >= 30){
                panic_mode = 0;
            }
        }

        /* Get the time in nano second at the end of the frame */
        clock_gettime(CLOCK_REALTIME, &new_time);

        refresh(end_time.tv_sec, new_time.tv_sec); /* Graphisme.h */
    }
    time_game = end_time.tv_sec - begin_time.tv_sec;
    free(walls);
    free(guards);
    free(reliques);

    if(quit >= 2){
        if(quit == 2){
            MLV_draw_text((SIZE_X*SCALE) / 3 , (SIZE_Y * SCALE) /3 +100, " SECONDS : %d MANA USED : %d/%d", (int)time_game , MAX_MANA - player.mana, MAX_MANA, MLV_COLOR_ORANGE1);  
            MLV_actualise_window();
            win_screen();
            printf("YOU WIN ");
        }
        else{
            MLV_draw_text((SIZE_X*SCALE) / 3 , (SIZE_Y * SCALE) /3 +100, " SECONDS : %d MANA USED : %d/%d", (int)time_game, MAX_MANA - player.mana, MAX_MANA, MLV_COLOR_ORANGE1);  
            MLV_actualise_window();
            loose_screen();
            printf("Game over !" );
        }
        free_music(music);
        free_image(image);
        MLV_free_window();
        printf("Seconds of game : %d seconds\nMana used: %d/%d ",  (int)time_game , MAX_MANA - player.mana, MAX_MANA);
    }

    MLV_wait_milliseconds(1000);
    return 0;
}
