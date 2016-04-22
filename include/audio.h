#ifndef AUDIO_H_
#define AUDIO_H_

#include "hovercraft.h"
#define MUS_PATH "son.wav"

// prototype for our audio callback
// see the implementation for more information
void my_audio_callback(void *userdata, Uint8 *stream, int len);

// variable declarations
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play

#endif
