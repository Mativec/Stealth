/**
 * @file Graphisme.c
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Implémentation du module graphique
 * @version 0.1
 * @date 2022-11-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../include/Graphisme.h"

void init_window() {
    MLV_create_window(NAME, ICON, SIZE_X, SIZE_Y);
    MLV_actualise_window();
}

void free_window() {
    MLV_free_window();
}

/*
void disp_coord(Engine_Obj player){
    //MLV_ text pour afficher les coordonnées a chaque framerate en haut a gauche de la page
}

*/

void draw_guard(Engine_Obj guard) {
    MLV_draw_filled_circle(guard.x, guard.y, 10, MLV_COLOR_BLUE);
}

/* faire le deplacement du garde toutes les secondes il va avancer d'un cran et chaque 3 seconde il toune
<-, <- , <- , | | | , ->, -> , -> , | | |
void deplacement_guard(Engine_Obj guard){
    Input

}
*/

void refresh(time_t end_time, time_t new_time) {
    int frametime, extratime;

    /* Compute the time spent for the current frame */
    frametime = new_time - end_time;
    frametime += (new_time - end_time) / 1.0E9;

    /* Force the program to spend at least 1/60 second in total*/
    extratime = 1.0 / 60 - frametime;
    if (extratime > 0) {
        MLV_wait_milliseconds((int)(extratime * 1000));
    }
    MLV_actualise_window();
}

void draw_window(Engine_Obj player, Engine_Obj guard) {
    static int init = 0;

    /* Window initiated ? */
    if (!init) {
        init = 1;
        init_window();
    }

    /* clean the window */
    MLV_clear_window(MLV_COLOR_WHITE);

    /* draw on the window */
    MLV_draw_filled_circle(player.x, player.y, 10, MLV_COLOR_RED);

    draw_guard(guard);
}
