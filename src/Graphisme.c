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

/*create the window*/
void init_window() {
    MLV_create_window(NAME, ICON, SIZE_X * SCALE, SIZE_Y * SCALE);
    MLV_actualise_window();
}



/*buttons of the menu*/
void buttons(){
    int width, height;

    width = SIZE_X * SCALE;
    height = SIZE_Y * SCALE;

    MLV_draw_text_box(width /2.4 , height / 2, width / 6 , height/ 9, "PLAY",120, MLV_COLOR_BLACK, MLV_COLOR_BLUE1, MLV_COLOR_YELLOW1, MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box(width /4.8 , height/2, width / 6 , height/ 9 , "SETTINGS",120, MLV_COLOR_BLACK, MLV_COLOR_BLUE1, MLV_COLOR_YELLOW1, MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box(width /1.6 , height/2 , width / 6, height/ 9 , "QUIT",120, MLV_COLOR_BLACK, MLV_COLOR_BLUE1, MLV_COLOR_YELLOW1, MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}


int title_screen(MLV_Image *image){
    int width, height;
    int x,y;
    int quit;

    width = SIZE_X * SCALE;
    height = SIZE_Y * SCALE;

    MLV_create_window( NAME, ICON, width, height );
    image = MLV_load_image("res/image_menu_sleath.jpg");
    MLV_resize_image(image, width, height);
    MLV_draw_image(image, 0 , 0);

    buttons();
    MLV_actualise_window();
    /*affichage du bouton jouer et des options et de quitter*/
    do{
        /*a travailler*/
        MLV_wait_mouse(&x, &y);
        if((x > width/ 2.4) && x < ((width/2.4) + (width / 6)) && (y > height / 2 ) && (y < height / 2 + (height / 9))){
            quit = 0;
            break;
        }
        if(x > width /1.6  &&  x < (width /1.6 + width/6) && y > height / 2 && y < (height / 2 + height/ 9)){
            quit = 1;
            break;
        }


    }
    while(x > 0 && x < width && y > 0 && y < height);
    free_window();
    return quit;
}



/*title screen for message when the player looses the game*/
void loose_screen(){
    MLV_draw_text_box(500, 450, 170, 110, "GAME OVER",120, MLV_COLOR_BLACK, MLV_COLOR_BLUE1, MLV_COLOR_RED1, MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_actualise_window();
    MLV_wait_seconds(3);
}


void win_screen(){
    MLV_draw_text_box(500, 450, 170, 110, "YOU WIN",120, MLV_COLOR_BLACK, MLV_COLOR_BLUE1, MLV_COLOR_GREEN1, MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_actualise_window();
    MLV_wait_seconds(3); 
}

/*draw walls*/
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

/*draw a relic with library*/
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

void draw_guards(Engine_Guard *guards) {
    int i;
    for (i = 0; i < NB_GUARDS; i++) {
        MLV_draw_filled_circle(guards[i].obj.x * SCALE, guards[i].obj.y * SCALE, SIZE_GUARD, MLV_COLOR_BLUE);
    }
}

/*draw the field of view of guard*/
void draw_fov_guards(Engine_Guard *guards, int panic_mode) {
    int i;
    int size;

    for (i = 0; i < NB_GUARDS; i++) {
        if(panic_mode){
            size = SIGHT_GUARDIAN_PANIC;
        } else{
            size = SIGHT_GUARDIAN;
        }
        MLV_draw_filled_circle(guards[i].obj.x * SCALE, guards[i].obj.y * SCALE, size * SCALE, MLV_COLOR_LIGHT_BLUE);
    }
}


/*refresh of the window*/
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


/*representation of the player with library*/
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

/*representation of animation when mode panic is on*/
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

void draw_window(Engine_Obj base, Engine_Player player, Engine_Guard *guards, int panic_mode, Engine_Walls walls, int nb_walls, Engine_Relique *reliques) {
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
    draw_fov_guards(guards, panic_mode);

    /* draw reliques */
    for (i = 0; i < NB_RELIQUES; i++) {
        draw_relique(reliques[i]);
    }

    /* draw player's spawn */
    offset = SCALE / 2;
    MLV_draw_filled_rectangle(base.x * SCALE - offset, base.y * SCALE - offset, SCALE * 1.5, SCALE * 1.5, MLV_COLOR_YELLOW1);

    /* draw guards */
    draw_guards(guards);

    /* draw player */
    draw_player(player);

    /* draw walls */
    for (i = 0; i < nb_walls; i++) {
        draw_wall(walls[i]);
    }

    draw_alert(panic_mode);
}
/* free window */
void free_window(){
    MLV_free_window();
}

/*free image */
void free_image(MLV_Image* image){
    MLV_free_image(image);
}