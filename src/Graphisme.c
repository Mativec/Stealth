/**
 * @file Graphisme.c
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Graphical module (source)
 * @version 0.1
 * @date 2022-11-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../include/Graphisme.h"

/**
 * @brief init the window where the game is displaying
 *
 */
void init_window() {
    MLV_create_window(NAME, ICON, SIZE_X * SCALE, SIZE_Y * SCALE);
    MLV_actualise_window();
}

/*title screen for message when the player looses the game*/
void loose_screen(){
    MLV_draw_text_box((SIZE_X * SCALE )/ 3+100, (SIZE_Y *SCALE )/ 2, 170, 110, "GAME OVER",120, MLV_COLOR_BLACK, MLV_COLOR_BLUE1, MLV_COLOR_RED1, MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_actualise_window();
    MLV_wait_mouse(NULL,NULL);
}


void win_screen(){
    MLV_draw_text_box((SIZE_X * SCALE) / 3+100, (SIZE_Y * SCALE) /2, 170, 110, "YOU WIN",120, MLV_COLOR_BLACK, MLV_COLOR_BLUE1, MLV_COLOR_GREEN1, MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_actualise_window();
    MLV_wait_mouse(NULL,NULL);
}
/**
 * @brief Draw a wall.
 *
 * @param wall : a wall.
 */
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

/**
 * @brief Draw a relic.
 *
 * @param relique : the relic to draw.
 */
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

/**
 * @brief draw the guards
 *
 * @param guards : a guard in game.
 */
void draw_guard(Engine_Guard guards) {
    MLV_draw_filled_circle(guards.obj.x * SCALE, guards.obj.y * SCALE, SIZE_GUARD, MLV_COLOR_BLUE);
}

/**
 * @brief draw the field of view of the enemies.
 *
 * @param guards : an array of enemies
 * @param panic_mode : is panic mode activated ?
 */
void draw_fov_guards(Engine_Guard *guards, int panic_mode) {
    int i;
    int size;
    MLV_Color color;

    for (i = 0; i < NB_GUARDS; i++) {
        if (panic_mode) {
            size = SIGHT_GUARDIAN_PANIC;
            color = MLV_COLOR_RED2;
        } else {
            size = SIGHT_GUARDIAN;
            color = MLV_COLOR_LIGHT_BLUE;
        }
        MLV_draw_filled_circle(guards[i].obj.x * SCALE, guards[i].obj.y * SCALE, size * SCALE, color);
    }
}

/**
 * @brief Draw player's spawn
 *
 * @param spawn : location where the player start the game (saved at start on main);
 */
void draw_spawn(Engine_Obj spawn) {
    int offset;

    offset = SCALE / 2;
    MLV_draw_filled_rectangle(spawn.x * SCALE - offset, spawn.y * SCALE - offset, SCALE * 1.5, SCALE * 1.5, MLV_COLOR_YELLOW1);
}

/**
 * @brief Draw the player and it's animation (skills)
 *
 * @param player : player in game.
 */
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

/**
 * @brief Draw an alert to inform the player that the panic mode is active.
 *
 * @param panic_mode : is panic mode activated ?
 */
void draw_alert(int panic_mode) {
    int i;
    Uint8 red, green, blue, alpha;

    if (panic_mode) {
        MLV_convert_color_to_rgba(MLV_COLOR_RED, &red, &green, &blue, &alpha);
        alpha /= 2;
        for (i = 0; i < 5; i++) {
            MLV_draw_rectangle(i, i, SIZE_X * SCALE - i, SIZE_Y * SCALE - i, MLV_convert_rgba_to_color(red, green, blue, alpha));
        }
    }
}

/**
 * @brief draw buttons for the player to interact with the title screen.
 *
 */
void buttons() {
    int width, height;

    width = SIZE_X * SCALE;
    height = SIZE_Y * SCALE;

    MLV_draw_text_box(width / 2.4, height / 2, width / 6, height / 9, "PLAY", 120, MLV_COLOR_BLACK, MLV_COLOR_BLUE1, MLV_COLOR_YELLOW1, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box(width / 4.8, height / 2, width / 6, height / 9, "HELP", 120, MLV_COLOR_BLACK, MLV_COLOR_BLUE1, MLV_COLOR_YELLOW1, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box(width / 1.6, height / 2, width / 6, height / 9, "QUIT", 120, MLV_COLOR_BLACK, MLV_COLOR_BLUE1, MLV_COLOR_YELLOW1, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

/**
 * @brief Draw the help_windows where is explaining how to play.
 *
 * @param width : width of the window
 * @param height : heights of the windows
 */
void help_window(int width, int height) {
    double x, y_player, y_relique, y_spawn;
    int y_guard;
    MLV_Image *background, *input, *space, *shift;
    Engine_Player *demo_player;
    Engine_Guard *demo_guard;
    Engine_Relique *demo_relique;
    Engine_Obj *demo_spawn;

    x = 5;
    y_player = 11;
    y_guard = 21;
    y_relique = 25;
    y_spawn = 30;

    /* Create demo_object */
    demo_player = init_player(x, y_player);
    demo_guard = init_guard((int)x, y_guard);
    demo_relique = init_relique(x, y_relique);
    demo_spawn = init_object(x, y_spawn);

    /* create the window */
    MLV_create_window(NAME, ICON, width, height);

    /* load resources */
    background = MLV_load_image(BACKGROUND_MENU);
    input = MLV_load_image("res/zqsd.png");
    space = MLV_load_image("res/space.png");
    shift = MLV_load_image("res/shift.png");

    /* resize them */
    MLV_resize_image(background, width, height);
    MLV_resize_image(input, 75, 50);
    MLV_resize_image(space, 75, 50);
    MLV_resize_image(shift, 75, 50);

    /* draw input demo */
    MLV_draw_image(background, 0, 0);
    MLV_draw_image(input, 50, 270);
    MLV_draw_image(shift, 700, 290);
    MLV_draw_image(space, 850, 290);

    MLV_draw_text(130, 290, "Utilisez ZQSD pour le déplacer., Vous pouvez également utiliser du mana pour aller plus vite ou vous rendre invisible!", MLV_COLOR_WHITE);

    /* draw player demo */
    draw_player(*demo_player);
    MLV_draw_text((x + 1) * SCALE, y_player * SCALE, "Voici votre personnage, avec sa jauge de mana.", MLV_COLOR_WHITE);

    /* draw guard demo */
    draw_guard(*demo_guard);
    MLV_draw_text((x + 1) * SCALE, y_guard * SCALE, "Voici un ennemi, attention à ne pas entrer dans son champs de vision !", MLV_COLOR_WHITE);

    x -= 2;

    /* draw relic demo */
    draw_relique(*demo_relique);
    MLV_draw_text((x + 4) * SCALE, y_relique * SCALE, "Voici une relique, vous devez toutes les attrapés ...", MLV_COLOR_WHITE);

    /* draw spawn demo */
    draw_spawn(*demo_spawn);
    MLV_draw_text((x + 4) * SCALE, y_spawn * SCALE, "... pour ensuite retourner au point de départ !", MLV_COLOR_WHITE);

    /* draw panic mode demo */
    MLV_draw_text(x * SCALE, (y_spawn + 5) * SCALE, "Et attention si les gardiens remarques l'absence d'une relique...", MLV_COLOR_WHITE);

    MLV_update_window();
    MLV_wait_mouse(NULL, NULL);

    /* free resources */
    MLV_free_image(background);
    MLV_free_image(input);
    MLV_free_image(shift);
    MLV_free_image(space);

    /* free demo objects */
    free(demo_player);
    free(demo_guard);
    free(demo_relique);
    free(demo_spawn);

    /* free window */
    MLV_free_window();
}

int title_screen(MLV_Image *image) {
    int width, height;
    int x, y;
    int quit;

    width = SIZE_X * SCALE;
    height = SIZE_Y * SCALE;

    MLV_create_window(NAME, ICON, width, height);
    image = MLV_load_image(BACKGROUND_MENU);
    MLV_resize_image(image, width, height);
    MLV_draw_image(image, 0, 0);

    buttons();
    MLV_actualise_window();
    /*affichage du bouton jouer et des options et de quitter*/
    do {
        /*a travailler*/
        MLV_wait_mouse(&x, &y);
        if ((x > width / 2.4) && x < ((width / 2.4) + (width / 6)) && (y > height / 2) && (y < height / 2 + (height / 9))) {
            quit = 0;
            break;
        } else if (x > width / 1.6 && x < (width / 1.6 + width / 6) && y > height / 2 && y < (height / 2 + height / 9)) {
            quit = 1;
            break;
        } else if (x > width / 4.8 && x < (width / 4.8 + width / 6) && y > height / 2 && y < (height / 2 + height / 9)) {
            MLV_free_window();
            help_window(width, height);
            return title_screen(image);
            break;
        }

    } while (x > 0 && x < width && y > 0 && y < height);
    MLV_free_window();
    return quit;
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
void draw_window(Engine_Obj base, Engine_Player player, Engine_Guard *guards, int panic_mode, Engine_Walls walls, int nb_walls, Engine_Relique *reliques) {
    static int init = 0;
    int i;

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
    draw_spawn(base);

    /* draw guards */

    for (i = 0; i < NB_GUARDS; i++) {
        draw_guard(guards[i]);
    }

    /* draw player */
    draw_player(player);

    /* draw walls */
    for (i = 0; i < nb_walls; i++) {
        draw_wall(walls[i]);
    }

    draw_alert(panic_mode);
}