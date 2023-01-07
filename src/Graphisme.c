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




void buttons(){
    MLV_draw_text_box(500, 450, 170, 110, "PLAY",120, MLV_COLOR_BLACK, MLV_COLOR_BLUE1, MLV_COLOR_YELLOW1, MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box(250, 450, 170, 110, "SETTINGS",120, MLV_COLOR_BLACK, MLV_COLOR_BLUE1, MLV_COLOR_YELLOW1, MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box(750, 450, 170, 110, "QUIT",120, MLV_COLOR_BLACK, MLV_COLOR_BLUE1, MLV_COLOR_YELLOW1, MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}


void title_screen(){
    int x,y;
    MLV_Image *image;

    MLV_create_window( "SLEATH", "image", SIZE_X, SIZE_Y );
    image = MLV_load_image("image_menu_s.jpg");
    MLV_resize_image_with_proportions(image, SIZE_X, SIZE_Y);
    MLV_draw_image(image, SIZE_ZERO , SIZE_ZERO);

    buttons();
    MLV_actualise_window();
    MLV_wait_mouse(&x,&y);
    /*affichage du bouton jouer et des options et de quitter*/
    do{
        MLV_wait_mouse(&x, &y);
        if(x >=170 && x <= 500 && y >= 110 && y <=450)
        printf("russi");

    }
    while(x > SIZE_X || y > SIZE_Y);

   free_window();
}




void loose_screen(){
    /*ne pas prendre , prendre celle du pplayer elle marche mieux*/
    MLV_free_window();
    init_window();
    MLV_draw_text_box(500, 450, 170, 110, "GAME OVER",120, MLV_COLOR_BLACK, MLV_COLOR_BLUE1, MLV_COLOR_YELLOW1, MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_wait_milliseconds(3);
    MLV_free_window();
}


void draw_window(Engine_Obj obj) {
    static int init = 0;


    /* Window initiated ? */
    if (!init) {
        init = 1;
        init_window();
    }

    /* clean the window */
    MLV_clear_window(MLV_COLOR_BLUE_VIOLET);

    


    /* draw on the window */
    MLV_draw_filled_circle(obj.x, obj.y, 10, MLV_COLOR_RED);
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
    MLV_actualise_window();
}

void free_window() {
    MLV_free_window();
}