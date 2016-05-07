#ifndef AUDIO_H_
#define AUDIO_H_

#include "hovercraft.h"
#define MUS_PATH "audio/son.wav"

static Uint8 *audio_pos;
static Uint32 audio_len;


/** Lecture du son **/
void my_audio_callback(void *userdata, Uint8 *stream, int len);



#endif
