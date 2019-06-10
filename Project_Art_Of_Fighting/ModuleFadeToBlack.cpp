#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"
#include "SDL_mixer/include/SDL_mixer.h"

ModuleFadeToBlack::ModuleFadeToBlack()
{
	screen = {0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE};
}

ModuleFadeToBlack::~ModuleFadeToBlack()
{}

// Load assets
bool ModuleFadeToBlack::Start()
{
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	IsFading = false;
	return true;
}

// Update: draw background
update_status ModuleFadeToBlack::Update()
{
	if(current_step == fade_step::none)
		return UPDATE_CONTINUE;

	Uint32 now = SDL_GetTicks() - start_time;
	float normalized = MIN(1.0f, (float)now / (float)total_time);

	switch(current_step)
	{
		case fade_step::fade_to_black:
		{
			App->input->Paused = true;
			if(now >= total_time)
			{
				//Fades music for 1 sec
				Mix_FadeOutMusic(1000);
				//Enables called module, disables current module
		

				moduleOff->Disable();
				App->player1->Disable();
				App->player2->Disable();
				moduleOn->Enable();


				//resets player & camera position
				App->render->camera.x = 0;
				App->render->camera.y = 0;
				
				total_time += total_time;
				start_time = SDL_GetTicks();
				current_step = fade_step::fade_from_black;
			}
		} break;

		case fade_step::fade_from_black:
		{
		//	App->scene_john->resetstage = true;
			normalized = 1.0f - normalized;
			if (now >= total_time) 
			{
				IsFading = false;
				current_step = fade_step::none;
			}
		} break;
	}

	// Finally render the black square with alpha on the screen
	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
	SDL_RenderFillRect(App->render->renderer, &screen);

	return UPDATE_CONTINUE;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool ModuleFadeToBlack::FadeToBlack(Module* module_off, Module* module_on, float time)
{
	moduleOff = module_off;
	moduleOn = module_on;

	IsFading = true;
	
	bool ret = false;

	if(current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		ret = true;
	}

	return ret;
}