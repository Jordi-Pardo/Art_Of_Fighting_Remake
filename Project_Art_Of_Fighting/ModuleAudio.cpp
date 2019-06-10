#include "Application.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )



ModuleAudio::ModuleAudio() : Module() {}

ModuleAudio::~ModuleAudio() {}


bool ModuleAudio::Init()
{
	bool ret = true;
	int Mix_AllocateChannels(16);
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		SDL_Log("SDL_INIT_AUDIO could not initialitze! SDL_Mix Error: %s\n", Mix_GetError());
		ret = false;
	}
	else
	{
		LOG("SDL_INIT AUDIO correctly initialized!\n");
		int flags = MIX_INIT_OGG;
		int initted = Mix_Init(flags);
		if (initted&flags != flags) {
			SDL_Log("Mix_Init: Failed to init required ogg support! SDL_Mixer Error: %s \n", Mix_GetError());
			SDL_Log("Mix_Init: %s\n", Mix_GetError());
			ret = false;
		}
		else
		{
			LOG("Mix_Init correctly initialized!");
			Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 512);
		}
	}
	return ret;
}


bool ModuleAudio::CleanUp()
{
	LOG("Cleaning music and fx!\n");
	
	for (unsigned int i = 0; i < last_audio; i++) {
		if(soundtrack[i]!=nullptr)
			Mix_FreeMusic(soundtrack[i]);
	}
	for (unsigned int i = 0; i < last_effect; i++)
		if (effects[i] != nullptr)
		Mix_FreeChunk(effects[i]);

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}

Mix_Music* const ModuleAudio::Load_music(const char *path)
{
Mix_Music* music = Mix_LoadMUS(path);
	soundtrack[last_audio++] = music;

	LOG("Loading Music\n");

	return music;
}

Mix_Chunk* const ModuleAudio::Load_effects(const char *path)
{
	Mix_Chunk* effect = Mix_LoadWAV(path);
	if (effect == NULL)
	{
		LOG("Llepala");
	}
	effects[last_effect++] = effect;

	LOG("Loading FX\n");
	
	return effect;
}

bool ModuleAudio::Play_music(Mix_Music* track)
{

	if (Mix_FadeInMusic(track, 0, 2000) == -1)
	{
		SDL_Log("%s/n", SDL_GetError());
		return false;
	}	
	Mix_Volume(2, 0);
	return true;
}

bool ModuleAudio::Play_chunk(Mix_Chunk* track)
{
	int num = Mix_PlayChannel(-1, track, 0);
	SDL_Log("%i",num);
	
		//SDL_Log("%s/n", SDL_GetError());
		//return false;
	
	return true;
}


bool ModuleAudio::Unload_music(Mix_Music* track)
{
	bool ret = false;

	if (track != nullptr)
	{
		for (int i = 0; i < MAX_MUS; ++i)
		{
			if (soundtrack[i] == track)
			{
				soundtrack[i] = nullptr;
				ret = true;
				last_audio--;
				Mix_FreeMusic(track);
				LOG("Efficiently cleaned music track!\n");
				break;
			}
		}
	}
	return ret;
}

bool ModuleAudio::Unload_effects(Mix_Chunk* track)
{
	bool ret = false;
	if (track != nullptr)
	{
		for (int i = 0; i < MAX_FX; ++i)
		{
			if (effects[i] == track)
			{
				effects[i] = nullptr;
				ret = true;
				last_effect--;
				Mix_FreeChunk(track);
				LOG("Efficiently cleaned chunk track!\n");
				break;
			}
		}	
	}
	return ret;
}