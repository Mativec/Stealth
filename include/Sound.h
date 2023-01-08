#ifndef __SOUND__
#define __SOUND__


#include "all.h"
#include <MLV/MLV_audio.h>



void play_sound(MLV_Music *music);



void free_music(MLV_Music* music);

#endif