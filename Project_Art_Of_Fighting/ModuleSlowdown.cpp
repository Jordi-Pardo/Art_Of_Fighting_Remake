#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleSlowdown.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"
#include "SDL/include/SDL_log.h"

ModuleSlowdown::ModuleSlowdown()
{
}

ModuleSlowdown::~ModuleSlowdown()
{}

// Load assets
bool ModuleSlowdown::Start()
{
	return true;
}

// Update: draw background
update_status ModuleSlowdown::PostUpdate()
{
	if (slowing_down)
	{
		UpdateSlowdown();
	}

	return UPDATE_CONTINUE;
}
void ModuleSlowdown::StartSlowdown(float duration, int magnitude)
{
	slowdown_timer = 0;
	slowdown_duration = duration;
	slowdown_magnitude = magnitude;
	slowing_down = true;
	this->magnitude = 0;
}

void ModuleSlowdown::UpdateSlowdown()
{
	time = slowdown_timer / slowdown_duration;
	if (time < 0.25f) {
		magnitude = slowdown_magnitude * time * 4;
	}
	else if (time > 0.75f) {
		magnitude = slowdown_magnitude * (1 - time) * 4;
	}
	if (time < 1) {
		slowdown_timer++;
		SDL_Delay(magnitude);
	}
	else {
		slowing_down = false;
	}

	SDL_Log("Time: %0.2f Magnitude: %i", slowdown_timer, magnitude);
}


