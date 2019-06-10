#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_joystick.h"
#include "ModulePlayer_1.h"

ModuleInput::ModuleInput() : Module()
{
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	for (int i = 0; i < 2; i++)
	{
		controller[i] = nullptr;
	}

	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);


	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{

		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	SDL_Joystick * joy = SDL_JoystickOpen(0);
	SDL_Joystick* joy1 = SDL_JoystickOpen(1);
	if (SDL_NumJoysticks() > 0) {
		joy = SDL_JoystickOpen(0);
		joy1 = SDL_JoystickOpen(1);
		if (joy) {
			LOG("\nOpened Joystick 0");
		}
	}
	if (SDL_JoystickIsHaptic(joy) == 1) {
		LOG("IS HAPTIC");
	}
	//Open the device
		haptic = SDL_HapticOpenFromJoystick(joy);
		haptic1 = SDL_HapticOpenFromJoystick(joy1);
		if (haptic == nullptr) {
			return -1;
		}
		if (SDL_HapticRumbleInit(haptic) == 0) {
			LOG("INNITED");
		}
		if (SDL_HapticRumbleInit(haptic1) == 0) {
			LOG("INNITED");
		}



	

	for (int i = 4; i < 285; i++)
	{
		keyboard_state[i] = KEY_IDLE;
	}

	int num = SDL_NumJoysticks();
	for (int i = 0; i < num; ++i) {
		if (SDL_IsGameController(i)) {
			controller[i] = SDL_GameControllerOpen(i);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (SDL_GameControllerGetAttached(controller[i])) {
			//LOG("&d TRUE",i)
		}
		else {
			//LOG("&d FALSE", i);
		}
	}


	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	if (SDL_NumJoysticks() == 2) {
		//LOG("2 PADS");
	}
	if (SDL_GameControllerGetAttached(controller[0])) {
		//LOG("TRUE")
	}
	else {
		if (SDL_NumJoysticks() > 0) {

			for (int i = 0; i < SDL_NumJoysticks(); ++i) {
				if (SDL_IsGameController(i)) {
					controller[i] = SDL_GameControllerOpen(i);
				}
			}
		}
		//LOG("FALSE");
	}

	if (Paused) {
		SDL_PumpEvents();
		if (App->player1->isJumping != true)
		{
			//App->player1->last_input = IN_UNKNOWN;
		}
		if (App->player2->isJumping != true)
		{
			//App->player2->last_input = IN_UNKNOWN;
		}

	}

	if (!Paused) 
	{
		SDL_PumpEvents();

		keyboard = SDL_GetKeyboardState(NULL);
		
		for (int i = 4; i < 285; i++)
		{
			if (keyboard[i] == 1)
			{
				if (keyboard_state[i] == KEY_IDLE)
					keyboard_state[i] = KEY_DOWN;
				else
					keyboard_state[i] = KEY_REPEAT;
			}
			else
			{
				if (keyboard_state[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
					keyboard_state[i] = KEY_UP;
				else
					keyboard_state[i] = KEY_IDLE;
			}
		}	
		
		if (controller[0] != nullptr) inputGamepad(1,controller[0]);
		if (controller[1] != nullptr) inputGamepad(2,controller[1]);

		if (App->scene_john->inGame) {
			//Joystick 01
			joystick_right_p1 = (GetHorizontalAxis_p1() > deathZone) ? true : false;
			joystick_left_p1 = (GetHorizontalAxis_p1() < -deathZone) ? true : false;

			joystick_up_p1 = (GetVerticalAxis_p1() < -jumpZone) ? true : false;
			joystick_down_p1 = (GetVerticalAxis_p1() > crouchZone) ? true : false;

			//Joystick 02
			joystick_right_p2 = (GetHorizontalAxis_p2() > deathZone) ? true : false;
			joystick_left_p2 = (GetHorizontalAxis_p2() < -deathZone) ? true : false;

			joystick_up_p2 = (GetVerticalAxis_p2() < -jumpZone) ? true : false;
			joystick_down_p2 = (GetVerticalAxis_p2() > crouchZone) ? true : false;
		}
		if (keyboard_state[SDL_SCANCODE_ESCAPE] == KEY_DOWN)
			return update_status::UPDATE_STOP;

		if (SDL_GameControllerGetButton(controller[0], SDL_CONTROLLER_BUTTON_BACK))
			return update_status::UPDATE_STOP;


	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{

	for (int i = 4; i < 285; i++)
	{
		keyboard_state[i] = KEY_IDLE;
	}
	Paused = true;
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

const float ModuleInput::GetHorizontalAxis_p1()
{
	float horizontalAxis = (float)SDL_GameControllerGetAxis(controller[0], SDL_CONTROLLER_AXIS_LEFTX);
	horizontalAxis /= 32767;

	return horizontalAxis;
}

const float ModuleInput::GetVerticalAxis_p1()
{
	float verticalAxis = (float)SDL_GameControllerGetAxis(controller[0], SDL_CONTROLLER_AXIS_LEFTY);
	verticalAxis /= 32767;

	return verticalAxis;
}
const float ModuleInput::GetHorizontalAxis_p2()
{
	float horizontalAxis = (float)SDL_GameControllerGetAxis(controller[1], SDL_CONTROLLER_AXIS_LEFTX);
	horizontalAxis /= 32767;

	return horizontalAxis;
}

const float ModuleInput::GetVerticalAxis_p2()
{
	float verticalAxis = (float)SDL_GameControllerGetAxis(controller[1], SDL_CONTROLLER_AXIS_LEFTY);
	verticalAxis /= 32767;

	return verticalAxis;
}

void ModuleInput::StartEffect()
{
		// Test the effect

}


void ModuleInput::inputGamepad(int numJoystick, SDL_GameController * controller) {
	if (numJoystick == 1) {
		//BUTTON A
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) == 1 && App->scene_john->inGame == true) {
			if (gamepad01.A == BUTTON_IDLE)
				gamepad01.A = BUTTON_DOWN;
			else
				gamepad01.A = BUTTON_REPEAT;
		}
		else
		{
			if (gamepad01.A == BUTTON_REPEAT || (gamepad01.A == BUTTON_DOWN))
				gamepad01.A = BUTTON_UP;
			else
				gamepad01.A = BUTTON_IDLE;
		}		
		//BUTTON Y
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y) == 1) {
			if (gamepad01.Y == BUTTON_IDLE)
				gamepad01.Y = BUTTON_DOWN;
			else
				gamepad01.Y = BUTTON_REPEAT;
		}
		else
		{
			if (gamepad01.Y == BUTTON_REPEAT || (gamepad01.Y == BUTTON_DOWN))
				gamepad01.Y = BUTTON_UP;
			else
				gamepad01.Y = BUTTON_IDLE;
		}

		//BUTTON X
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X) == 1) {
			if (gamepad01.X == BUTTON_IDLE)
				gamepad01.X = BUTTON_DOWN;
			else
				gamepad01.X = BUTTON_REPEAT;
		}
		else
		{
			if (gamepad01.X == BUTTON_REPEAT || (gamepad01.X == BUTTON_DOWN))
				gamepad01.X = BUTTON_UP;
			else
				gamepad01.X = BUTTON_IDLE;
		}

		//BUTTON B
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B) == 1 && App->scene_john->inGame == true) {
			if (gamepad01.B == BUTTON_IDLE)
				gamepad01.B = BUTTON_DOWN;
			else
				gamepad01.B = BUTTON_REPEAT;
		}
		else
		{
			if (gamepad01.B == BUTTON_REPEAT || (gamepad01.B == BUTTON_DOWN))
				gamepad01.B = BUTTON_UP;
			else
				gamepad01.B = BUTTON_IDLE;
		}

		//BUTTON START
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START) == 1) {
			if (gamepad01.START == BUTTON_IDLE)
				gamepad01.START = BUTTON_DOWN;
			else
				gamepad01.START = BUTTON_REPEAT;
		}
		else
		{
			if (gamepad01.START == BUTTON_REPEAT || (gamepad01.START == BUTTON_DOWN))
				gamepad01.START = BUTTON_UP;
			else
				gamepad01.START = BUTTON_IDLE;
		}
	}
	if (numJoystick == 2) {
		//BUTTON A
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) == 1) {
			if (gamepad02.A == BUTTON_IDLE)
				gamepad02.A = BUTTON_DOWN;
			else
				gamepad02.A = BUTTON_REPEAT;
		}
		else
		{
			if (gamepad02.A == BUTTON_REPEAT || (gamepad02.A == BUTTON_DOWN))
				gamepad02.A = BUTTON_UP;
			else
				gamepad02.A = BUTTON_IDLE;
		}
		//BUTTON Y
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y) == 1) {
			if (gamepad02.Y == BUTTON_IDLE)
				gamepad02.Y = BUTTON_DOWN;
			else
				gamepad02.Y = BUTTON_REPEAT;
		}
		else
		{
			if (gamepad02.Y == BUTTON_REPEAT || (gamepad02.Y == BUTTON_DOWN))
				gamepad02.Y = BUTTON_UP;
			else
				gamepad02.Y = BUTTON_IDLE;
		}
		//BUTTON X
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X) == 1) {
			if (gamepad02.X == BUTTON_IDLE)
				gamepad02.X = BUTTON_DOWN;
			else
				gamepad02.X = BUTTON_REPEAT;
		}
		else
		{
			if (gamepad02.X == BUTTON_REPEAT || (gamepad02.X == BUTTON_DOWN))
				gamepad02.X = BUTTON_UP;
			else
				gamepad02.X = BUTTON_IDLE;
		}

		//BUTTON B
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B) == 1) {
			if (gamepad02.B == BUTTON_IDLE)
				gamepad02.B = BUTTON_DOWN;
			else
				gamepad02.B = BUTTON_REPEAT;
		}
		else
		{
			if (gamepad02.B == BUTTON_REPEAT || (gamepad02.B == BUTTON_DOWN))
				gamepad02.B = BUTTON_UP;
			else
				gamepad02.B = BUTTON_IDLE;
		}

		//BUTTON START
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START) == 1) {
			if (gamepad02.START == BUTTON_IDLE)
				gamepad02.START = BUTTON_DOWN;
			else
				gamepad02.START = BUTTON_REPEAT;
		}
		else
		{
			if (gamepad02.START == BUTTON_REPEAT || (gamepad02.START == BUTTON_DOWN))
				gamepad02.START = BUTTON_UP;
			else
				gamepad02.START = BUTTON_IDLE;
		}
	}

}
void ModuleInput::StartHaptic(SDL_Haptic* haptic)
{
	SDL_HapticRumblePlay(haptic, 1.0f, 75);

}
