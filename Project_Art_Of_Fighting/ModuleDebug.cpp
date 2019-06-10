#include "Application.h"
#include "ModuleDebug.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"
#include "ModuleInput.h"
#include <stdio.h>

bool ModuleDebug::Init()
{
	square_pos.x = 0;
	square_pos.y = 0;

	point.rect = { 0,0,10,10 };

	graphic = App->textures->Load("Assets/red_square.png");
	LOG("\n\nModuleDebug Init");

	return true;
}
bool ModuleDebug::Start() {
	App->fonts->Load("Assets/fonts/small_white_font.png", " abcdefghiklmnoprstuwy!.0123456789", 2, 8, 8, 34);
	debug = false;
	return true;
}

update_status ModuleDebug::Update()
{


	if (App->input->keyboard_state[SDL_SCANCODE_F2] == KEY_DOWN){     //F2== amagar o enseñar debug
		debug = !debug;
	}
	if (debug == false)
		return update_status::UPDATE_CONTINUE;


	App->fonts->BlitText(5, 11, 3, "pad 0 plugged press 1.2.3 for rumble");
	App->fonts->BlitText(5, 20, 3, "buttons");
	App->fonts->BlitText(5, 29, 3, "dpad");
	App->fonts->BlitText(5, 38, 3, "left trigger"); //ficar el right i que es tradueixi de float a string.
	App->fonts->BlitText(5, 50, 3, "right thumb"); //ficar el right i que es tradueixi de float a string.
	App->fonts->BlitText(5, 59, 3, "hor asis"); //ficar el right i que es tradueixi de float a string.
	App->fonts->BlitText(120, 59, 3, "ver asis"); //ficar el right i que es tradueixi de float a string.

	numControllers = SDL_NumJoysticks();
	sprintf_s(controllers, 40, "num controllers: %d",numControllers);
	App->fonts->BlitText(5, 2, 3,controllers);
	if (App->input->GetHorizontalAxis_p1() > App->input->deathZone)
	sprintf_s(time, 10, "%.2f", App->input->GetHorizontalAxis_p1());
	else if (App->input->GetHorizontalAxis_p1() < -App->input->deathZone) {
		sprintf_s(time, 10, "%.2f", App->input->GetHorizontalAxis_p1());
	}	
	if (App->input->GetVerticalAxis_p1() > App->input->deathZone)
	sprintf_s(time2, 10, "%.2f", App->input->GetVerticalAxis_p1());
	else if (App->input->GetVerticalAxis_p1() < -App->input->deathZone) {
		sprintf_s(time2, 10, "%.2f", App->input->GetVerticalAxis_p1());
	}
	if (App->input->GetHorizontalAxis_p1() > App->input->deathZone || App->input->GetHorizontalAxis_p1() < -App->input->deathZone) {
		App->fonts->BlitText(85, 59, 3, time);
	}
	else
	{
		App->fonts->BlitText(85, 59, 3, "0.0");
	}
	if (App->input->GetVerticalAxis_p1() > App->input->deathZone || App->input->GetVerticalAxis_p1() < -App->input->deathZone) {
		App->fonts->BlitText(200, 59, 3, time2);
	} //ficar el right i que es tradueixi de float a string.
	else
	{
		App->fonts->BlitText(200, 59, 3, "0.0");
	}

//	LOG("- ModuleDebug Update");
	return update_status::UPDATE_CONTINUE;
}

bool ModuleDebug::CleanUp()
{
	/*App->fonts->UnLoad(0);
	App->textures->Unload(graphic);
	LOG("- ModuleDebug CleanUp");*/
	return true;
}

void ModuleDebug::ShowDebug(iPoint * player)
{
	/*App->render->Blit(graphic,player->x,player->y,&point);*/
}
