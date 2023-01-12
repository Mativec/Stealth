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

void draw_wall(Engine_Wall wall) {
    float x, y, width, height;

    x = wall.obj.x;
    y = wall.obj.y;
    width = SIZE_WALL;
    height = SIZE_WALL;

    switch (wall.orientation) {
        case OBJECT_LEFT:
            x -= wall.size;
            width = wall.size;
            break;

        case OBJECT_RIGHT:
            width = wall.size;
            break;

        case OBJECT_UP:
            y -= wall.size;
            height = wall.size;
            break;

        case OBJECT_DOWN:
            height = wall.size;
            break;

        default:
            break;
    }

    x = (x - SIZE_WALL / 2) * SCALE;
    y = (y - SIZE_WALL / 2) * SCALE;
    width *= SCALE;
    height *= SCALE;

    MLV_draw_filled_rectangle(x, y, width, height, MLV_COLOR_GRAY25);
}

void draw_relique(Engine_Relique relique) {
    Uint8 red, green, blue, alpha;
    MLV_Color color;

    color = MLV_COLOR_GREEN1;

    MLV_convert_color_to_rgba(color, &red, &green, &blue, &alpha);

    if (relique.is_picked_up) {
        alpha /= 3;
    }
    MLV_draw_filled_rectangle(
        relique.obj.x * SCALE,
        relique.obj.y * SCALE,
        SCALE, SCALE,
        MLV_convert_rgba_to_color(red, green, blue, alpha));
}

void draw_guards(Engine_Guard *guards, int nb_guards) {
    int i;
    for (i = 0; i < nb_guards; i++) {
        MLV_draw_filled_circle(guards[i].obj.x * SCALE, guards[i].obj.y * SCALE, SIZE_GUARD, MLV_COLOR_BLUE);
    }
}

void draw_fov_guards(Engine_Guard *guards, int nb_guards, int panic_mode) {
    int i;
    int size;

    for (i = 0; i < nb_guards; i++) {
        if(panic_mode){
            size = SIGHT_GUARDIAN_PANIC;
        } else{
            size = SIGHT_GUARDIAN;
        }
        MLV_draw_filled_circle(guards[i].obj.x * SCALE, guards[i].obj.y * SCALE, size * SCALE, MLV_COLOR_LIGHT_BLUE);
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

void draw_player(Engine_Player player) {
    float length, width, offset;
    Uint8 red, green, blue, alpha;

    width = 10;
    length = 20;
    offset = 15;

    MLV_convert_color_to_rgba(MLV_COLOR_RED, &red, &green, &blue, &alpha);
    if (player.overcharge) {
        MLV_draw_filled_circle(player.obj.x * SCALE, player.obj.y * SCALE, SIZE_PLAYER * SCALE + 2, MLV_COLOR_GREY1);
    }
    if (player.invisibility) {
        alpha /= 2;
    }
    MLV_draw_filled_circle(player.obj.x * SCALE, player.obj.y * SCALE, SIZE_PLAYER * SCALE, MLV_convert_rgba_to_color(red, green, blue, alpha));

    /* Mana jauge */
    MLV_draw_rectangle(player.obj.x * SCALE + offset, player.obj.y * SCALE - offset, length, width, MLV_COLOR_GREY);
    if (player.mana > 0) {
        MLV_draw_filled_rectangle(player.obj.x * SCALE + offset, player.obj.y * SCALE - offset, (player.mana * length) / MAX_MANA, width, MLV_COLOR_BLUE);
    }
}

void draw_alert(int panic_mode) {
    int i;
    Uint8 red, green, blue, alpha;

    if (panic_mode) {
        MLV_convert_color_to_rgba(MLV_COLOR_RED, &red, &green, &blue, &alpha);
        alpha /= 2;
        for(i = 0; i < 5; i++){
            MLV_draw_rectangle(i, i, SIZE_X* SCALE - i, SIZE_Y * SCALE - i, MLV_convert_rgba_to_color(red, green, blue, alpha));
        }
    }
}

void draw_window(Engine_Obj base, Engine_Player player, Engine_Guard *guards, int nb_guards, int panic_mode, Engine_Walls walls, int nb_walls, Engine_Relique *reliques, int nb_reliques) {
    static int init = 0;
    int i, offset;

    /* Window initiated ? */
    if (!init) {
        init = 1;
        init_window();
    }

    /* clean the window */
    MLV_clear_window(MLV_COLOR_WHITE);

    /* draw guard's fov */
    draw_fov_guards(guards, nb_guards, panic_mode);

    /* draw reliques */
    for (i = 0; i < nb_reliques; i++) {
        draw_relique(reliques[i]);
    }

    /* draw player's spawn */
    offset = SCALE / 2;
    MLV_draw_filled_rectangle(base.x * SCALE - offset, base.y * SCALE - offset, SCALE * 1.5, SCALE * 1.5, MLV_COLOR_YELLOW1);

    /* draw guards */
    draw_guards(guards, nb_guards);

    /* draw player */
    draw_player(player);

    draw_player(player);

    /* draw walls */
    for (i = 0; i < nb_walls; i++) {
        draw_wall(walls[i]);
    }

    draw_alert(panic_mode);
}
