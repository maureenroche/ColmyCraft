#include "../include/audio.h"

/** Lecture du son **/
void my_audio_callback(void *userdata, Uint8 *stream, int len)
{

	if (audio_len ==0) return;
	len = ( len > audio_len ? audio_len : len );
	//SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}
