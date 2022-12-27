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
#include <MLV/MLV_time.h>

#include "../include/all.h"

int main(int argc, char* argv[]) {
    struct timespec end_time, new_time;
    Engine_Input event;
    Engine_Obj object;
    int play;


/*******************************************************************************/
    /*DEV : OBJECT PLAYER AND GUARD*/

    Engine_Guard guard;

    guard = *init_guard(400, 400);

/*******************************************************************************/

    play = 1;
    object = *init_object(500, 500, SPEED);

    /* Main loop over the frames... */
    while (play) {
        /*Some declaration of variables*/

        /*Get the time in nano second at the start of the frame */
        clock_gettime(CLOCK_REALTIME, &end_time);

        /* Display of the currentframe, samplefunction */
        /* THIS FUNCTION CALLS ONCE AND ONLY ONCE MLV_update_window */
        draw_window(object, *(guard.obj)); /* Graphisme.h */


        /* We get here some keyboard events*/
        event = get_event(); /* Input.h */

        /* Dealing with the events */
        if (event != INPUT_NONE) {
            /*
            printf("%s\n", input_to_string(event));
            */
        }
        
        play *= (event != INPUT_QUIT);

        /* Move the entities on the grid */
        move_player(&object, event);


        /* Collision detection and other game mechanisms */
        if(out_of_bound(&object)){
             move_object(&object, OBJECT_REVERT);
        }
        /* gerer un deplacement aleatoire et si le gardien touche un mur ou un out of band il revert sur une autre pos */
        move_guard(&guard);
/*******************************************************************************/
        /*Colision between gard and player*/
        play *= !(collision(*(guard.obj), object));


/*********************************************************************************************/

        /* Get the time in nano second at the end of the frame */
        clock_gettime(CLOCK_REALTIME, &new_time);
        refresh(end_time.tv_sec, new_time.tv_sec); /* Graphisme.h */
    }
    MLV_wait_seconds(1);
    free_window();

    return 0;
}
