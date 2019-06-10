#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneTodo.h"
#include "ModuleInput.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneJohn.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"
#include"ModuleUI.h"
#include "ModuleFonts.h"


ModuleSceneTodo::ModuleSceneTodo()
{
	rect_background.rect.w = 556;
	rect_background.rect.h = 224;
	rect_background.rect.x = 0;
	rect_background.rect.y = 338;

	indicator.rect.x = 0;
	indicator.rect.y = 96;
	indicator.rect.h = 16;
	indicator.rect.w = 100;

	timeup.rect.x = 0;
	timeup.rect.y = 129;
	timeup.rect.w = 104;
	timeup.rect.h = 16;

	nthng.PushBack({ 120,23,104,16 },0,0,30);
	nthng.speed = 0.15f;

	winp1.PushBack({ 0,40,116,40 }, 0, 0, 30);
	winp1.speed = 0.15f;
	
	winp2.PushBack({ 0,0,120,40 },0 , 0,30 );
	winp2.speed = 0.15f;

	
}

ModuleSceneTodo::~ModuleSceneTodo()
{}


bool ModuleSceneTodo::Start()
{
	current_animation = &nthng;
	first_row = true;
	//timeup.ResetCurrentFrame();
	tick1 = 0;
	tick1 = SDL_GetTicks();
	LOG("Loading todo scene");
	todo_music = App->audio->Load_music("Assets/Audio/033xART OF FIGHT.ogg");
	fightfx = App->audio->Load_effects("Assets/Audio/FX/Fight.wav");
	App->audio->Play_music(todo_music);
	graphics = App->textures->Load("Assets/backgrounds_karuta_guardian.png");
	//App->collision->AddCollider({ {300,0,30,224},{0,0} }, COLLIDER_WALL);

	App->player1->Enable();
	App->player2->Enable();
	App->sceneUI->Enable();

	App->input->keyboard_state[SDL_SCANCODE_RETURN] = KEY_IDLE;


	indicator_fight = App->textures->Load("Assets/UI_Sprites/indicator_fight.png");

	return true;
}

update_status ModuleSceneTodo::Update()
{

	if ((App->render->Blit(graphics, 0, 0, &rect_background)) == false )
	{
		SDL_Log("Unable to [BLIT] texture: texture_background");
		return update_status::UPDATE_STOP;
	}
	if (tick2 - tick1 < 2000) {
	
		if (rounds_counter == 0)
		{
			indicator.rect.x = 0;
			indicator.rect.y = 96;
			indicator.rect.w = 100;
			indicator.rect.h = 16;
			App->render->Blit(indicator_fight, (SCREEN_WIDTH / 2) - 50, (SCREEN_HEIGHT / 2) - 8, &indicator, 0);
		}
		if (rounds_counter == 1)
		{
			indicator.rect.x = 0;
			indicator.rect.y = 80;
			indicator.rect.w = 104;
			indicator.rect.h = 16;
			App->render->Blit(indicator_fight, (SCREEN_WIDTH / 2) - 50, (SCREEN_HEIGHT / 2) - 8, &indicator, 0);
		}
		if (rounds_counter >1)
		{
			indicator.rect.x = 0;
			indicator.rect.y = 145;
			indicator.rect.w = 168;
			indicator.rect.h = 16;
			App->render->Blit(indicator_fight, (SCREEN_WIDTH / 2) - 85, (SCREEN_HEIGHT / 2) - 30, &indicator, 0);
		}	
	}
	
	if (tick2-tick1>2000 && tick2 - tick1 < 4000) {
		
		if (first_row == true)
		{
			App->audio->Play_chunk(fightfx);
		}
		indicator.rect.x = 0;
		indicator.rect.y = 113;
		indicator.rect.h = 16;
		indicator.rect.w = 80;
		App->render->Blit(indicator_fight, (SCREEN_WIDTH / 2)-40, (SCREEN_HEIGHT / 2)-8, &indicator, 0);
		first_row = false;
	}

	//TIME UP//
	if (App->sceneUI->time_over == true)
	{
		App->input->Paused = true;

		if (App->player1->isJumping != true)
		{
			App->player1->current_state = ST_IDLE;
			App->player1->last_input = IN_UNKNOWN;
		}
		if (App->player2->isJumping != true)
		{
			App->player2->current_state = ST_IDLE;
			App->player2->last_input = IN_UNKNOWN;
		}

		if (App->player1->Player_Health_Value_p1 > App->player2->Player_Health_Value_p2)
		{
			current_animation = &winp2;
		}
		
		if (App->player2->Player_Health_Value_p2 > App->player1->Player_Health_Value_p1)
		{
			current_animation = &winp1;
		}

		
		
		App->player1->CheckHealth(*App->player2);
		App->player2->CheckHealth(*App->player1);
		
			App->render->Blit(indicator_fight, (SCREEN_WIDTH / 2) - 50, (SCREEN_HEIGHT) / 2 - 8, &timeup, 0);
			App->render->Blit(indicator_fight, 145, 45, &current_animation->GetCurrentFrame(), 0);
			if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 1)
			{
				if (App->player2->p1_win < 2 && App->player1->p2_win < 2)
				{
					App->fade->FadeToBlack(App->scene_todo, App->scene_todo);
				}
				else
				{
					App->fade->FadeToBlack(App->scene_todo, App->scene_congratz);
				}
			}
		
	}

	if (App->player2->win_check == true)
	{
		current_animation = &winp1;
	
		App->input->Paused = true;

		if (App->player1->isJumping != true)
		{
			App->player1->current_state = ST_IDLE;
			App->player1->last_input = IN_UNKNOWN;
		}

		if (App->player2->isJumping != true)
		{
			App->player2->current_state = ST_IDLE;
			App->player2->last_input = IN_UNKNOWN;
		}
		App->render->Blit(indicator_fight, 145, 65, &current_animation->GetCurrentFrame(), 0);
		if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 1)
		{
			if (App->player2->p1_win < 2)
			{
				App->fade->FadeToBlack(App->scene_todo, App->scene_todo);
			}
			else
			{
				App->fade->FadeToBlack(App->scene_todo, App->scene_congratz);
			}
		}
	}

	if (App->player1->win_check == true)
	{
		current_animation = &winp2;

		App->input->Paused = true;

		if (App->player2->isJumping != true)
		{
			App->player2->current_state = ST_IDLE;
			App->player2->last_input = IN_UNKNOWN;
		}

		if (App->player1->isJumping != true)
		{
			App->player1->current_state = ST_IDLE;
			App->player1->last_input = IN_UNKNOWN;
		}

		
		App->render->Blit(indicator_fight, 145, 65, &current_animation->GetCurrentFrame(), 0);
		if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 1)
		{
			if (App->player1->p2_win < 2)
			{
				App->fade->FadeToBlack(App->scene_todo, App->scene_todo);
			}
			else
			{
				App->fade->FadeToBlack(App->scene_todo, App->scene_congratz);
			}
		}
	}


	//JOHN SCENE
	if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN && !App->input->Paused)
	{
		App->fade->FadeToBlack( App->scene_todo, App->scene_john);
	}

	tick2 = SDL_GetTicks();
	return UPDATE_CONTINUE;
}

bool ModuleSceneTodo::CleanUp()
{
	if (FrontPanel && BackPanel)
	{
		FrontPanel->to_delete = true;
		BackPanel->to_delete = true;
	}
	App->audio->Unload_music(todo_music);
	App->audio->Unload_effects(fightfx);
	App->textures->Unload(indicator_fight);
	App->textures->Unload(graphics);
	App->player1->Disable();
	App->player2->Disable();
	App->sceneUI->Disable();
	


	//RESET
	App->sceneUI->time_over = false;
	App->player1->win_check = false;
	App->player2->win_check = false;
	//ROUNDS_COUNTER
	if (current_animation != &nthng && current_animation != nullptr)
	{
		rounds_counter++;
	}
	LOG("Unloading todo scene");
	return true;
}