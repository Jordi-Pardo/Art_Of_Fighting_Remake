#ifndef _ModuleCongratzScreen_H_
#define _ModuleCongratzScreen_H_

#include "Module.h"
#include "Globals.h"
#include "Animation.h"

class ModuleCongratzScreen :public Module {
public:
	ModuleCongratzScreen();
	~ModuleCongratzScreen();
	bool Start();
	update_status Update();
	bool CleanUp();
public:
	bool result;
	Mix_Music * ending_music = nullptr;
	Mix_Chunk* select = nullptr;
	SDL_Texture* graphics = nullptr;
	Animation countback;
	Animation* current_animation;
	Animation zero;
	RectSprites chat_bubble;
	RectSprites rect_win;
	RectSprites rect_lose;
	uint beat_by_1 = 0;
	uint beat_by_2 = 0;
};

#endif