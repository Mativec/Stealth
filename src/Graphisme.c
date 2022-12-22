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
    MLV_create_window(NAME, ICON, SIZE_X * SCALE, SIZE_Y * SCALE);
    MLV_actualise_window();
}

void draw_wall(Wall wall) {
    int width, height;

    width = SIZE_WALL;
    height = SIZE_WALL;

    if (wall.orientation == OBJECT_LEFT || wall.orientation == OBJECT_RIGHT) {
        width = wall.size;
    }
    if (wall.orientation == OBJECT_UP || wall.orientation == OBJECT_DOWN) {
        height = wall.size;
    }

    MLV_draw_filled_rectangle(
        wall.coord.x * SCALE - SIZE_WALL / 2,
        wall.coord.y * SCALE - SIZE_WALL / 2,
        width * SCALE,
        height * SCALE,
        MLV_COLOR_GRAY25);
}

void draw_window(Engine_Obj obj, Walls walls, int nb_walls) {
    static int init = 0;
    int i;

    /* Window initiated ? */
    if (!init) {
        init = 1;
        init_window();
    }

    /* clean the window */
    MLV_clear_window(MLV_COLOR_WHITE);

    /* draw on the window */
    MLV_draw_filled_circle(
        obj.x * SCALE,
        obj.y * SCALE,
        SIZE_PLAYER * SCALE,
        MLV_COLOR_RED);

    /* draw walls */
    for (i = 0; i < nb_walls; i++) {
        draw_wall(walls[i]);
    }
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
    MLV_actualise_window();
}

void free_window() {
    MLV_free_window();
}