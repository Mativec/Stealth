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

#include "Graphisme.h"

void init_window() {
    MLV_create_window(NAME, NULL, SIZE_X, SIZE_Y);
    MLV_clear_window(MLV_COLOR_WHITE);
}

void draw_window() {
    static int init = 0;
    if (!init) {
        init = 1;
        init_window();
    }
    return;
}

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
}

void free_window() {
    MLV_free_window();
}