#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"

#define MAX_MUS 10
#define MAX_FX 500

struct Mix_Music;
struct Mix_Chunk;

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();
	Mix_Music* soundtrack[MAX_MUS];
	Mix_Chunk* effects[MAX_FX];
	uint last_audio = 0;
	uint last_effect = 0;
	

	



	bool Init();
	bool CleanUp();
	Mix_Music* const Load_music(const char* path);
	Mix_Chunk* const Load_effects(const char* path);
	bool Play_music(Mix_Music* track);
	bool Play_chunk(Mix_Chunk* track);
	bool Unload_music(Mix_Music* track);
	bool Unload_effects(Mix_Chunk* track);
};


#endif