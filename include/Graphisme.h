/**
 * @file Graphisme.h
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Module graphique
 * @version 0.1
 * @date 2022-11-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __GRAPHISME__
#define __GRAPHISME__

#include <MLV/MLV_color.h>
#include <MLV/MLV_shape.h>
#include <MLV/MLV_time.h>
#include <MLV/MLV_window.h>
#include <MLV/MLV_mouse.h>
#include <MLV/MLV_text.h>

#include <string.h>

#include "Config.h"
#include "Object.h"
#include "Player.h"
#include "Relique.h"
#include "Guards.h"
#include "Wall.h"




/**
 * @brief Draw a the menu withs buttons 
 * 
 * @param base 
 * @param player 
 * @param guards 
 * @param nb_guards 
 * @param panic_mode 
 * @param walls 
 * @param nb_walls 
 * @param reliques 
 * @param nb_reliques 
 */
void draw_window(Engine_Obj base, Engine_Player player, Engine_Guard *guards, int nb_guards, int panic_mode, Engine_Walls walls, int nb_walls, Engine_Relique *reliques, int nb_reliques);


/**
 * @brief updates the display and ensures the correct framerate*
 * 
 * @param end_time 
 * @param new_time 
 * @return * updates 
 */
void refresh(time_t end_time, time_t new_time);


/**
 * @brief returns 1 if the game is quit otherwise 0
 * 
 * @param image 
 * @return int 
 */
int title_screen(MLV_Image *image);


/**
 * @brief free the actually window
 * 
 */
void free_window();

/**
 * @brief  free the image was loaded
 * 
 * @param image 
 */
void free_image(MLV_Image* image);



/**
 * @brief message in title screen when player looses the game
 * 
 */
void loose_screen();


/**
 * @brief when the player win the game , message of win appears.
 * 
 */
void win_screen();
#endif
