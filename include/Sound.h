#ifndef __SOUND__
#define __SOUND__


#include "all.h"
#include <MLV/MLV_audio.h>


/**
 * @brief play music in the game
 * 
 * @param music 
 */
void play_sound(MLV_Music *music);


/**
 * @brief free the music at the end of game
 * 
 * @param music 
 */
void free_music(MLV_Music* music);

#endif