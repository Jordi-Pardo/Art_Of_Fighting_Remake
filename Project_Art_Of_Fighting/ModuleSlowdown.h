#ifndef __MODULESLOWDOWN_H__
#define __MODULESLOWDOWN_H__

#include "Module.h"
#include "SDL\include\SDL_rect.h"

class ModuleSlowdown : public Module
{
public:
	ModuleSlowdown();
	~ModuleSlowdown();

	bool Start();
	update_status PostUpdate();

	void StartSlowdown(float duration, int magnitude);
	void UpdateSlowdown();

private:
	bool slowing_down = false;

	float slowdown_duration = 0;
	float slowdown_timer = 0;
	float time = 0;
	float timing = 0;
	int magnitude = 0;
			
	int slowdown_magnitude = 0;

};

#endif //__MODULEFADETOBLACK_H__