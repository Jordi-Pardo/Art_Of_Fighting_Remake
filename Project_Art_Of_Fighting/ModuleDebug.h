#ifndef __ModuleDebug_H__
#define __ModuleDebug_H__
#include "Module.h"
#include "Globals.h"
#include "RectSprites.h"
#include "SDL_image/include/SDL_image.h"
#include "Animation.h"

class ModuleDebug : public Module {
public:
	RectSprites point;
	bool debug = true;
	Animation idle;
	SDL_Texture * graphic;
	SDL_Texture * graphic_player;
	iPoint square_pos;

	int numControllers;

	char time[10];
	char time2[10];
	char controllers[40];
public:

	bool Init() override;
	bool Start() override;
	update_status Update() override;
	bool CleanUp() override;

	void ShowDebug(iPoint *);

};

#endif // !__ModuleDebug_H__
