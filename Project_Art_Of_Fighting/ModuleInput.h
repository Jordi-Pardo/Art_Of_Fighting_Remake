#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_gamecontroller.h"
#include "SDL/include/SDL_haptic.h"

typedef unsigned char Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	void inputGamepad(int numJoystick,SDL_GameController *);
	void StartHaptic(SDL_Haptic*);

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	const Uint8 *keyboard = nullptr;
	SDL_GameController *controller[2];

	
	int effect_id;

	bool Paused = false;

	bool jump = true;

	float deathZone = 0.4f;
	float jumpZone = 0.7f;
	float crouchZone = 0.8f;

	const float GetHorizontalAxis_p1();
	const float GetVerticalAxis_p1();
	const float GetHorizontalAxis_p2();
	const float GetVerticalAxis_p2();

	void StartEffect();

	key_state keyboard_state[285];
	GamePad gamepad01;
	GamePad gamepad02;
	SDL_Haptic* haptic = nullptr;
	SDL_Haptic* haptic1 = nullptr;

	bool joystick_up_p1;
	bool joystick_down_p1;
	bool joystick_left_p1;
	bool joystick_right_p1;
	bool joystick_left_repeat_p1;
	bool joystick_right_repeatp1;

	bool joystick_up_p2;
	bool joystick_down_p2;
	bool joystick_left_p2;
	bool joystick_right_p2;
	bool joystick_left_repeat_p2;
	bool joystick_right_repeatp2;



};

#endif // __ModuleInput_H__