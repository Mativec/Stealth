/**
 * @file Sound.h
 * @author Richard ARNAOUT, Matias VECCHIO
 * @brief Sound manager for the game (header)
 * @version 0.1
 * @date 2023-01-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __SOUND__
#define __SOUND__

#include <MLV/MLV_audio.h>

#include "all.h"

/**
 * @brief play music in the game
 *
 * @param music
 */
void play_sound(MLV_Music* music);

/**
 * @brief free the music at the end of game
 *
 * @param music
 */
void free_music(MLV_Music* music);

#endif