#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneTodo.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleSceneJohn.h"
#include "ModuleSceneTodo.h"
#include "ModuleCongratzScreen.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomeScreen.h"
#include"ModuleUI.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleFonts.h"
#include "ModuleDebug.h"
#include "ModuleCharacter_Selection.h"
#include "RectSprites.h"
#include <stdio.h>



ModuleWelcomeScreen::ModuleWelcomeScreen()
{
	//logo transition//
	//c1
	logo_transition.PushBack({ 0,0,309,232 });
	logo_transition.PushBack({ 0,232,309,232 });
	logo_transition.PushBack({ 0,464,309,232 });
	logo_transition.PushBack({ 0,696,309,232 });
	logo_transition.PushBack({ 0,928,309,232 });
	logo_transition.PushBack({ 0,1160,309,232 });
	logo_transition.PushBack({ 0,1392,309,232 });
	logo_transition.PushBack({ 0,1624,309,232 });
	//c2
	logo_transition.PushBack({ 309,0,309,232 });
	logo_transition.PushBack({ 309,232,309,232 });
	logo_transition.PushBack({ 309,464,309,232 });
	logo_transition.PushBack({ 309,696,309,232 });
	logo_transition.PushBack({ 309,928,309,232 });
	logo_transition.PushBack({ 309,1160,309,232 });
	logo_transition.PushBack({ 309,1392,309,232 });
	logo_transition.PushBack({ 309,1624,309,232 });
	//c3
	logo_transition.PushBack({ 618,0,309,232 });
	logo_transition.PushBack({ 618,232,309,232 });
	logo_transition.PushBack({ 618,464,309,232 });
	logo_transition.PushBack({ 618,696,309,232 });
	logo_transition.PushBack({ 618,928,309,232 });
	logo_transition.PushBack({ 618,1160,309,232 });
	logo_transition.PushBack({ 618,1392,309,232 });
	logo_transition.PushBack({ 618,1624,309,232 });
	logo_transition.PushBack({ 618,1624,309,232 });
	logo_transition.PushBack({ 618,1624,309,232 });

	//c4
	logo_transition.PushBack({ 927,0,309,232 });
	logo_transition.PushBack({ 927,232,309,232 });
	logo_transition.PushBack({ 927,464,309,232 });
	logo_transition.PushBack({ 927,696,309,232 });
	logo_transition.PushBack({ 927,928,309,232 });
	logo_transition.PushBack({ 927,1160,309,232 });
	logo_transition.PushBack({ 927,1392,309,232 });
	logo_transition.PushBack({ 927,1624,309,232 });
	//c5
	logo_transition.PushBack({ 1236,0,309,232 });
	logo_transition.PushBack({ 1236,232,309,232 });
	logo_transition.PushBack({ 1236,464,309,232 });
	logo_transition.PushBack({ 1236,696,309,232 });
	logo_transition.PushBack({ 1236,928,309,232 });
	logo_transition.PushBack({ 1236,1160,309,232 });
	logo_transition.PushBack({ 1236,1392,309,232 });
	logo_transition.PushBack({ 1236,1624,309,232  });
	//c6
	logo_transition.PushBack({ 1545,0,309,232 });
	logo_transition.PushBack({ 1545,0,309,232 });
	logo_transition.PushBack({ 1545,0,309,232 });
	logo_transition.PushBack({ 1545,0,309,232 });
	logo_transition.PushBack({ 1545,0,309,232 });
	logo_transition.PushBack({ 1545,0,309,232 });
	logo_transition.PushBack({ 1545,0,309,232 });
	logo_transition.speed = 0.4f;

	//Final_logo
	final_logo.PushBack({ 1609,244,216,130 });


	insert_coin.PushBack({ 1574,1100,140,10 });
	insert_coin.PushBack({ 1574,1133,140,10 });
	insert_coin.speed = 0.07f;
	

	snk.rect = { 1547,1141,77,25 };

	black.rect = { 100,150,120,10 };
	current_animation = &logo_transition;

	

}

ModuleWelcomeScreen::~ModuleWelcomeScreen()
{}

bool ModuleWelcomeScreen::Init()
{
	App->debug->Disable();
	App->scene_john->Disable();
	App->scene_todo->Disable();
	App->scene_congratz->Disable();
	App->character_selection->Disable();
	App->sceneUI->Disable();
	return true;
}

bool ModuleWelcomeScreen::Start()
{

	onlyonce = 0;
	LOG("Loading intro scene");
	if ((graphics = App->textures->Load("Assets/WelcomeScreen.png")) == NULL)
	{
		SDL_Log("Could not load image from path! SDL_Error: %s", SDL_GetError());
		return false;
	}
	start_music = App->audio->Load_music("Assets/Audio/041xRyukoh-no Theme.ogg");
	brokenglass = App->audio->Load_effects("Assets/Audio/FX/Brokenglass.wav");	
	select= App->audio->Load_effects("Assets/audio/FX/select.wav");
	cuadro = App->textures->Load("Assets/cuadro.png");
	cuadroRoto = App->textures->Load("Assets/cuadro roto.png");
	tick1 = SDL_GetTicks();
	tick4 = SDL_GetTicks();

	color.x = 0;
	color.y = 0;
	color.w = SCREEN_WIDTH;
	color.h = SCREEN_HEIGHT;


	return true;
}


update_status ModuleWelcomeScreen::Update()
{
	App->input->Paused = false;

	if (sequence1 == true) {
		secondScreen();
	}
	else {
		thirdScreen();
	}
	if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN || App->input->gamepad01.START == BUTTON_DOWN || App->input->gamepad02.START == BUTTON_DOWN) coins++;
	sprintf_s(coinsText, 20, "coins   %d", coins);
	App->fonts->BlitText(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 10, 2, coinsText);


	return update_status::UPDATE_CONTINUE;
}


bool ModuleWelcomeScreen::CleanUp()
{
	App->fonts->UnLoad(0);
	App->audio->Unload_music(start_music);
	App->audio->Unload_effects(brokenglass);
	App->audio->Unload_effects(select);
	App->textures->Unload(graphics);
	App->textures->Unload(cuadro);
	App->textures->Unload(cuadroRoto);

	LOG("Unloading welcome scene");
	return true;
}

void ModuleWelcomeScreen::thirdScreen() {
	tick3 = SDL_GetTicks();
	timer2 = SDL_GetTicks();
	if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 1)
	{
		finish_animation = 1;
		current_animation = &final_logo;
	}
	else
	{
		App->render->Blit(graphics, 25, 0, &current_animation->GetCurrentFrame());
	}

	if (finish_animation == 1) {
		App->render->Blit(graphics, 60, 180, &snk);

		App->render->Blit(graphics, 89, 12, &current_animation->GetCurrentFrame());

		App->fonts->BlitText(61, 205, 2, "snk home entertainment, inc.!1992");
		if(tick3 - tick4 >= 1000) {
			App->fonts->BlitText(106, 150, 2, "push 1p start button");
			if (tick3 - tick4 >= 2000) {
				tick4 = SDL_GetTicks();
			}
		}
		//App->render->Blit(graphics, 130, 150, &insert_coin.GetCurrentFrame());
	}	



	if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN || App->input->gamepad01.START == BUTTON_DOWN || App->input->gamepad02.START == BUTTON_DOWN)
	{
		App->audio->Play_chunk(select);
		App->fade->FadeToBlack(App->scene_welcome, App->character_selection);
		App->input->Enable();
	}
	//if (SDL_GameControllerGetButton(App->input->controller[0], SDL_CONTROLLER_BUTTON_START)) {
	//	App->fade->FadeToBlack(App->scene_welcome, App->scene_todo);
	//	App->input->Enable();
	//}


	if (App->input->keyboard_state[SDL_SCANCODE_0] == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_welcome, App->scene_congratz);
	}
	//Canviar al nivell de Cina
	if (App->input->keyboard_state[SDL_SCANCODE_M] == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_welcome, App->scene_john);
	}
	if (timer2 - timer1 > 2000 && timer2-timer1<30000) {
		sprintf_s(time, 20, "%d", 30 - ((timer2 - timer1) / 1000));
		if (30 - ((timer2 - timer1) / 1000) < 10) {
			App->fonts->BlitText((SCREEN_WIDTH / 2), 170, 5, time);
			App->fonts->BlitText((SCREEN_WIDTH / 2)-6, 170, 5, "0");			
		}
		else {
			App->fonts->BlitText((SCREEN_WIDTH / 2) - 6, 170, 5, time);
		}
		App->fonts->BlitText((SCREEN_WIDTH / 2) - 12, 160, 5, "time");
	}
	if (timer2 - timer1 > 30000 && coins!=0) {
		App->fade->FadeToBlack(App->scene_welcome, App->character_selection);
	}
	else {
		timer2 = SDL_GetTicks();
	}
}
void ModuleWelcomeScreen::secondScreen() {
	tick3 = SDL_GetTicks();

	App->render->DrawQuad(color, 64, 16, 0, 255);
	RendPosition = { {0,0,304,224},{0,0},{0,0} };
	if (tick2 - tick1 < 3100) {
		App->render->Blit(cuadro, (SCREEN_WIDTH / 2) - 152, (SCREEN_HEIGHT / 2) - 112, &RendPosition, 1, 1, false);
	}
	else {
		if (onlyonce == 0)
		{
			App->audio->Play_chunk(brokenglass);
			onlyonce++;
		}
		App->render->Blit(cuadroRoto, (SCREEN_WIDTH / 2) - 152, (SCREEN_HEIGHT / 2) - 112, &RendPosition, 1, 1, false);
	}
	if (tick3 - tick4 >= 1000) {
		App->fonts->BlitText((SCREEN_WIDTH / 2) - 44, (SCREEN_HEIGHT / 2) + 15, 2, "insert coin");
		if (tick3 - tick4 >= 2000) {
			tick4 = SDL_GetTicks();
		}
	}
	if (tick2 - tick1 > 3000 && tick2 - tick1 < 3200) {
		App->render->DrawQuad(color, 255, 255, 255, 255);
	}

	if (fadeSlow != 0) {
		App->render->DrawQuad(color, 0, 0, 0, fadeSlow);
		fadeSlow -= 1;
	}
	if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN || App->input->gamepad01.START == BUTTON_DOWN || App->input->gamepad02.START == BUTTON_DOWN) {
		App->audio->Play_music(start_music);
		sequence1 = false;
		timer1 = SDL_GetTicks();
	}
	if (tick2 - tick1 > 6500)
	{
		App->audio->Play_music(start_music);
		sequence1 = false;
		timer1 = SDL_GetTicks();
	}

	tick2 = SDL_GetTicks();
}