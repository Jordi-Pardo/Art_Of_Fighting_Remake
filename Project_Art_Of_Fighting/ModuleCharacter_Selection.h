#ifndef _MODULECHARACTERSELECTION_
#define _MODULECHARACTERSELECTION_

#include "Application.h"
#include "Globals.h"
#include "Animation.h"
#include "Module.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "RectSprites.h"

struct Mix_Music;
struct Mix_Chunk;


class ModuleScreenSelection : public Module {
public:
	ModuleScreenSelection();
	~ModuleScreenSelection();
	bool Init();
	bool CleanUp();
	update_status Update();
	bool Start();
	void timer();
	void draw();
	void choose();
	void characters_enter();

	SDL_Rect back;

	RectSprites imageSelection1;
	RectSprites imageSelection2;
	RectSprites john_other;
	RectSprites characters;
	RectSprites name1;
	RectSprites name2;
	RectSprites not_available;
	Animation vs;
	Animation vs_final;

	SDL_Renderer* background;
	SDL_Texture* graphics;

	Animation selector1;
	Animation selector2;
	Mix_Music* selection_music;
	Mix_Music* character_music;
	Mix_Chunk* player1_john;
	Mix_Chunk* player2_john;
	Mix_Chunk* versus;
	Mix_Chunk* select;

	bool selected = false;
	bool timer_init = false;
	int onlyonetime;

	int SELECTOR_1 = 2;
	int SELECTOR_2 = 2;

	int john1counter;
	int john2counter;
	int versuscounter;

	int X_SELECTOR_1 = (SCREEN_WIDTH / 2) + 28;
	int Y_SELECTOR_1 = (SCREEN_HEIGHT / 2) + 75;
	int X_SELECTOR_2 = (SCREEN_WIDTH / 2) + 28;
	int Y_SELECTOR_2 = (SCREEN_HEIGHT / 2) + 78;

	int tick1 = 0, tick2 = 0;
	char time_char[10];
	int time_int;
	bool no_zero;

	int x_image1 = -140, x_image2 = SCREEN_WIDTH + 10;
	int x_name1 = -140, x_name2 = SCREEN_WIDTH + 10;
};

#endif // !_MODULECHARACTERSELECTION_
