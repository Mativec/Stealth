/**
 * @file Graphisme.h
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Graphical module (header)
 * @version 0.1
 * @date 2022-11-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __GRAPHISME__
#define __GRAPHISME__

#include <MLV/MLV_color.h>
#include <MLV/MLV_mouse.h>
#include <MLV/MLV_shape.h>
#include <MLV/MLV_text.h>
#include <MLV/MLV_time.h>
#include <MLV/MLV_window.h>
#include <string.h>

#include "Config.h"
#include "Guards.h"
#include "Object.h"
#include "Player.h"
#include "Relique.h"
#include "Wall.h"

/**
 * @brief Draw a the menu withs buttons
 *
 * @param base : player's spawn.
 * @param player : the player.
 * @param guards : array of the NB_GUARDS enemies.
 * @param panic_mode : is panic_mode activated ?
 * @param walls : array of all the walls in game.
 * @param nb_walls : number of wall in game.
 * @param reliques : array of NB_RELIQUES reliques.
 */
void draw_window(Engine_Obj base, Engine_Player player, Engine_Guard *guards, int panic_mode, Engine_Walls walls, int nb_walls, Engine_Relique *reliques);

/**
 * @brief updates the display and ensures the correct framerate
 * all the parameters are updated for the next frame.
 *
 * @param end_time : end time of the last frame
 * @param new_time : start time of the current frame.
 */
void refresh(time_t end_time, time_t new_time);

/**
 * @brief returns 1 if the game is quit otherwise 0
 *
 * @param image : background image
 * @return int
 */
int title_screen(MLV_Image *image);

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
