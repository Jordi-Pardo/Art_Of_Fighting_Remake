#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleCongratzScreen.h"
#include "ModuleSceneTodo.h"
#include "ModuleUI.h"
#include "SDL/include/SDL.h"
#include "ModuleFonts.h"
#include "ModuleDebug.h"
#include "ModuleCharacter_Selection.h"

ModuleCongratzScreen::ModuleCongratzScreen()
{
	countback.PushBack({1858,932,80,96 });
	countback.PushBack({1968,932,80,96 });
	countback.PushBack({1859,1069,80,96 });
	countback.PushBack({1968,1069,80,96 });
	countback.PushBack({1858,1165,80,96 });
	countback.PushBack({1968,1165,80,96 });
	countback.PushBack({1858,1301,80,96 });
	countback.PushBack({1968,1301,80,96 });
	countback.PushBack({1858,1397,80,96 });
	countback.PushBack({1968,1397,80,96 });
	countback.speed = 0.015f;

	zero.PushBack({ 1968,1397,80,96 });

	rect_win.rect.x = 1549;
	rect_win.rect.y = 799;
	rect_win.rect.w = 128;
	rect_win.rect.h = 128;

	chat_bubble.rect.x = 1547;
	chat_bubble.rect.y = 1085;
	chat_bubble.rect.w = 272;
	chat_bubble.rect.h = 48;
}

ModuleCongratzScreen::~ModuleCongratzScreen(){}

bool ModuleCongratzScreen::Start()
{
	App->debug->Disable();
	App->sceneUI->Disable();
	LOG("Loading congratz scene");
	if ((graphics = App->textures->Load("Assets/WelcomeScreen.png")) == NULL)
	{
		SDL_Log("Could not load image from path! SDL_Error: %s", SDL_GetError());
		return false;
	}	
	ending_music = App->audio->Load_music("Assets/Audio/042xSono hito-wa watashitachi-no kodomo kana.ogg");
	select = App->audio->Load_effects("Assets/audio/FX/select.wav");
	App->audio->Play_music(ending_music);

	//if (App->player1->Player_Health_Value <= 0)
	//{
	//	beat_by_2++;
	//	result = false;
	//}
	//if (App->player2->Player_Health_Value <= 0)
	//{
	//	beat_by_1++;
	//	result = true;
	//}

	if (App->player1->p2_win == 2)
	{
		result = false;
	}
	else
	{
		result = true;
	}

	current_animation = &countback;
	current_animation->ResetCurrentFrame();

	//Load fonts



	return true;
}

update_status ModuleCongratzScreen::Update()
{
	App->fonts->BlitText(220, 47, 2, "waiting for");
	App->fonts->BlitText(215, 58, 2, "a challenger");
	App->input->Paused = false;
	if ((App->render->Blit(graphics, 50, 164, &chat_bubble,1.0f,1,false)) == false)
	{
		SDL_Log("Unable to [BLIT] texture: texture_background");
			return update_status::UPDATE_STOP;
	}
	App->render->Blit(graphics, 57.5, 36, &rect_win, 1.0f, 1, false);
	App->fonts->BlitText(58.5, 173, 1, "what ya lookin' at? if you wanna");
	App->fonts->BlitText(58.5, 188, 1, "start somethin', lets do it!");
	
	
	App->render->Blit(graphics, 220, 68.5, &current_animation->GetCurrentFrame(), 1.0f, 1, false);
 
	//When using this, coliders do not render 
	if (App->input->keyboard_state[SDL_SCANCODE_Q] == KEY_DOWN || App->input->gamepad01.START == BUTTON_DOWN || App->input->gamepad02.START == BUTTON_DOWN)
	{
		App->audio->Play_chunk(select);
		App->fade->FadeToBlack(App->scene_congratz, App->character_selection);
	}

	if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame()-1)
	{	
		current_animation = &zero;
		App->fade->FadeToBlack(App->scene_congratz, App->character_selection);
	}
	return update_status::UPDATE_CONTINUE;
}

bool ModuleCongratzScreen::CleanUp()
{
	App->textures->Unload(graphics);
	App->audio->Unload_music(ending_music);
	App->audio->Unload_effects(select);
	App->player1->p2_win = 0;
	App->player2->p1_win = 0;
	App->sceneUI->counter1 = 0;
	App->sceneUI->counter2 = 0;
	App->scene_todo->rounds_counter = 0;
	App->scene_john->rounds_counter = 0;
		LOG("Unloading congratz scene");
	return true;
}