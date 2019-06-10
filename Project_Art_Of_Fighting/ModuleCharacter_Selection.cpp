#include "ModuleCharacter_Selection.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "ModuleSceneTodo.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleRender.h"
#include "RectSprites.h"
#include "ModuleFonts.h"
#include <stdio.h>
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "John.h"

ModuleScreenSelection::ModuleScreenSelection() {
	back.w = SCREEN_WIDTH;
	back.h = SCREEN_HEIGHT;
	back.x = 0;
	back.y = 0;

	characters.rect.x = 0;
	characters.rect.y = 138;
	characters.rect.w = 112;
	characters.rect.h = 56;

	selector1.PushBack({ 0,194,28,31 });
	selector1.PushBack({ 500,500,28,31 });
	selector1.speed = 0.8f;

	selector2.PushBack({ 28,194,28,31 });
	selector2.PushBack({ 500,500,28,31 });
	selector2.speed = 0.8f;

	imageSelection2.rect.x = 128;
	imageSelection2.rect.y = 0;
	imageSelection2.rect.w = 128;
	imageSelection2.rect.h = 128;

	name1.rect.x = 0;
	name1.rect.y = 123;
	name1.rect.w = 58;
	name1.rect.h = 15;

	not_available.rect.x = 0;
	not_available.rect.y = 225;
	not_available.rect.w = 112;
	not_available.rect.h = 56;

	john_other.rect.x = 256;
	john_other.rect.y = 0;
	john_other.rect.w = 128;
	john_other.rect.h = 128;


	int x = 0, y = 281, w = 50, h = 32;
	for (int i=0; i <= 15; i++) {
		vs.PushBack({ x,y,w,h });
		y += 32;
	}
	vs_final.PushBack({ 0,729,w,h });
	vs.loop = false;
	vs.speed = 0.5f;
}
ModuleScreenSelection::~ModuleScreenSelection() {

}

bool ModuleScreenSelection::Init() {
	SDL_SetRenderDrawColor(background,0, 0, 0, 255);
	SDL_RenderFillRect(background, &back);
	SDL_RenderPresent;
	return true;
}
bool ModuleScreenSelection::Start() {
	onlyonetime = 0;
	john1counter = 0;
	john2counter = 0;
	versuscounter = 0;
	x_image1 = -140, x_image2 = SCREEN_WIDTH + 10;
	x_name1 = -140, x_name2 = SCREEN_WIDTH + 10;
	int SELECTOR_1 = 2;
	int SELECTOR_2 = 2;
	selected = false;
	graphics = App->textures->Load("Assets/character_selection.png");
	selection_music = App->audio->Load_music("Assets/Audio/Donokagoshi.ogg");
	character_music = App->audio->Load_music("Assets/Audio/058x200yen Arigatou.ogg");
	player1_john = App->audio->Load_effects("Assets/Audio/FX/John_1.wav");
	player2_john = App->audio->Load_effects("Assets/Audio/FX/John_2.wav");
	select = App->audio->Load_effects("Assets/audio/FX/select.wav");
	versus = App->audio->Load_effects("Assets/Audio/FX/Versus.wav");
	App->input->Paused = false;
	tick1 = SDL_GetTicks();
	no_zero = true;
	App->audio->Play_music(selection_music);
	return true;
}
update_status ModuleScreenSelection::Update() {
	if (selected == false) {
		if (no_zero == true) {
			time_int = (10000 + (tick1 - tick2)) / 1000;
		}
		sprintf_s(time_char, 10, "%.0i", time_int);


		choose();
		draw();
		timer();
	}
	else { //Quan clicas intro
		if (onlyonetime == 0)
		{
			tick1 = SDL_GetTicks();
			App->audio->Play_chunk(select);
			onlyonetime++;
		}
		
		if (timer_init == false) {
			tick1 = SDL_GetTicks();
			timer_init = true;
		}
		tick2 = SDL_GetTicks();
		//VS//


		//character image animation
		
		characters_enter();



		if (tick2 - tick1 > 2500) {
			App->fade->FadeToBlack(App->character_selection, App->scene_john);
		}
	} 

	return UPDATE_CONTINUE;
}
bool ModuleScreenSelection::CleanUp() {
	App->textures->Unload(graphics);
	App->audio->Unload_music(character_music);
	App->audio->Unload_effects(player1_john);
	App->audio->Unload_effects(player2_john);
	App->audio->Unload_effects(versus);
	App->audio->Unload_effects(select);
	onlyonetime = 0;
	john1counter = 0;
	john2counter = 0;
	versuscounter = 0;
	tick1 = SDL_GetTicks();
	vs.ResetCurrentFrame();
	no_zero = true;
	int SELECTOR_1 = 2;
	int SELECTOR_2 = 2;
	selected = false;
	x_image1 = -140, x_image2 = SCREEN_WIDTH + 10;
	x_name1 = -140, x_name2 = SCREEN_WIDTH + 10;
	return true;
}
void ModuleScreenSelection::timer() {
	if (time_int <= 0) {
		tick1 = 0;
		tick2 = 0;
		no_zero = false;
		App->fonts->BlitText((SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 - 32, 2, "0");
		//App->fade->FadeToBlack(App->character_selection, App->scene_john);
		selected = true;
	}
	tick2 = SDL_GetTicks();
}
void ModuleScreenSelection::draw() {
	App->render->Blit(graphics, (SCREEN_WIDTH / 2) - 56, (SCREEN_HEIGHT / 2) + 50, &characters, 1.0f, 1, false);
	App->render->Blit(graphics, (SCREEN_WIDTH / 2) - 56, (SCREEN_HEIGHT / 2) + 50, &not_available, 1.0f, 1, false);
	App->render->Blit(graphics, X_SELECTOR_1, Y_SELECTOR_1, &selector1.GetCurrentFrame(), 1.0f, 1, false);
	App->render->Blit(graphics, X_SELECTOR_2, Y_SELECTOR_2, &selector2.GetCurrentFrame(), 1.0f, 1, false);
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 83, 15, 1, "vs mode select player"); 
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 16, SCREEN_HEIGHT / 2 - 40, 2, "time");
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 8, SCREEN_HEIGHT / 2 - 32, 2, "0");
	App->fonts->BlitText((SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 - 32, 2, time_char);
}
void ModuleScreenSelection::choose() {

	if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN || App->input->gamepad01.Y == BUTTON_DOWN || App->input->gamepad02.Y == BUTTON_DOWN) {
		selected = true;
		//App->fade->FadeToBlack(App->character_selection, App->scene_todo, 0.7f);
	}


	//JOHN
	if (SELECTOR_1==2) {
		App->render->Blit(graphics, 35, 10, &imageSelection2, 1.0f, 1, false);
		App->render->Blit(graphics, 70, 140, &name1, 1.0f, 1, false);
		if (SELECTOR_2==2) {
			App->render->Blit(graphics, SCREEN_WIDTH - 165, 10, &john_other, 1.0f, 1, false);
			App->render->Blit(graphics, 35 + SCREEN_WIDTH - 165, 140, &name1, 1.0f, 1, false);
		}
	}

}
void ModuleScreenSelection::characters_enter() {
	App->audio->Unload_music(selection_music);
	if (john1counter == 0)
	{
		App->audio->Play_music(character_music);
		App->audio->Play_chunk(player1_john);
		john1counter++;
	}

	if (SELECTOR_1 == 2) {
		if (x_image1 == 20) {
			App->render->Blit(graphics, x_image1, 15, &imageSelection2, 1, 1, false);
		}
		else {
			x_image1 += 10;
			App->render->Blit(graphics, x_image1, 15, &imageSelection2, 1, 1, false);
		}
		if (tick2 - tick1 > 50) {
			if (x_name1 >= 58) {
				App->render->Blit(graphics, x_name1 - 5, 145, &name1, 1, 1, false);
			}
			else {
				x_name1 += 10;
				App->render->Blit(graphics, x_name1 - 5, 145, &name1, 1, 1, false);
			}
		}
	}
	if (tick2 - tick1 > 1600)
	{
		if (versuscounter == 0)
		{
			App->audio->Play_chunk(versus);
			versuscounter++;
		}
	}
	if (tick2 - tick1 > 1200) {
		App->render->Blit(graphics, (SCREEN_WIDTH / 2) - 25, (SCREEN_HEIGHT / 2) - 16, &vs.GetCurrentFrame(), 1.0f, 1, false);
		if (vs.GetCurrentFramePos() == vs.GetLastFrame() - 1) {
			App->render->Blit(graphics, (SCREEN_WIDTH / 2) - 25, (SCREEN_HEIGHT / 2) - 16, &vs_final.GetCurrentFrame(), 1.0f, 1, false);
		}
	}
	if (tick2 - tick1 > 2400) {

		if (SELECTOR_2 == 2) {
			if (x_image2 <= (SCREEN_WIDTH / 2) + 50) {
				App->render->Blit(graphics, x_image2, 15, &john_other, 1, 1, false);
			}
			else {
				x_image2 -= 10;
				App->render->Blit(graphics, x_image2, 15, &john_other, 1, 1, false);
			}
			if (tick2 - tick1 > 2500) {

				if (x_image2 <= (SCREEN_WIDTH / 2) + 70) {
					App->render->Blit(graphics, x_name2 - 50, 145, &name1, 1, 1, false);
				}
				else {
					x_name2 -= 10;
					App->render->Blit(graphics, x_name2 - 50, 145, &name1, 1, 1, false);
				}
			}
		}
	}
	if (tick2 - tick1 > 2600) {

		if (john2counter == 0)
		{
			App->audio->Play_chunk(player2_john);
			john2counter++;
		}

	}
}