#ifndef _ModuleWelcomeScreen_H_
#define _ModuleWelcomeScreen_H_

#include "Module.h"
#include "Globals.h"
#include "Animation.h"

struct SDL_Texture;


class ModuleWelcomeScreen : public Module {
public:
	ModuleWelcomeScreen();
	~ModuleWelcomeScreen();

	bool Init()override;
	bool Start()override;
	update_status Update()override;

	bool CleanUp();
	void secondScreen();
	void thirdScreen();

public:
	int onlyonce;
	enum screen_state
	{
		MOVING,
		NOT_MOVING,
	};
	Animation* current_animation;
	Mix_Chunk* brokenglass;
	Mix_Chunk* select;
	screen_state state = MOVING;
	SDL_Texture* graphics = nullptr;

	SDL_Texture* cuadro = nullptr;
	SDL_Texture* cuadroRoto = nullptr;
	SDL_Rect color;
	RectSprites RendPosition;
	SDL_Renderer* render;

	Mix_Music* start_music = nullptr;
	RectSprites rect_background;
	Animation logo_transition;
	Animation insert_coin;
	Animation final_logo;
	int finish_animation = 0;
	RectSprites snk;
	RectSprites black;

	int fadeSlow = 255;
	int tick1 = 0, tick2 = 0, tick3 = 0, tick4 = 0;
	int timer1 = 0, timer2 = 0;
	char coinsText[20];
	int coins = 0;

	char time[20];
	bool sequence1 = true;


};



#endif
