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
#include <string.h>

#include "Config.h"
#include "Object.h"
#include "Player.h"
#include "Guards.h"
#include "Wall.h"

void draw_window(Engine_Player player, Engine_Guard *guard, int nb_guards, Engine_Walls walls, int nb_walls);

void refresh(time_t end_time, time_t new_time);

void free_window();

#endif
