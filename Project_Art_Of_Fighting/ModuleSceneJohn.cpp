#include "Globals.h"
#include "Application.h"
#include "ModuleSceneJohn.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCongratzScreen.h"
#include"ModuleCollision.h"
#include"ModuleUI.h"
#include "SDL/include/SDL.h"
#include "ModuleDebug.h"


// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneJohn::ModuleSceneJohn()
{
	//background//
	rect_background.rect.w = 557;
	rect_background.rect.h = 225;
	rect_background.rect.x = 0;
	rect_background.rect.y = 0;

	//rojo parpadeo//
	rojoParpadeo.PushBack({ 174, 224, 24, 32 });
	rojoParpadeo.PushBack({ 198,224,24,32 });
	rojoParpadeo.speed = 0.2f;


	//rotulo verde//
	rotuloVerde.PushBack({ 0,224,77,19 });
	rotuloVerde.PushBack({ 77,224,77,19 });
	rotuloVerde.speed = 0.1f;

	//radio//
	radio.PushBack({ 0,242,36,31 });
	radio.PushBack({ 36,242,36,31 });
	radio.PushBack({ 72,242,36,31 });
	radio.PushBack({ 108,242,36,31  });
	radio.speed = 0.1f;

	//szechu//
	szechu.PushBack({ 154,224,10,73 });
	szechu.PushBack({ 164,224,10,73 });
	szechu.speed = 0.1f;

	//Morado//
	morado.PushBack({ 50,274,50,43 },0,0,3);
	morado.PushBack({  0,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 13);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 13);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 13);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 13);
	morado.speed = 0.2f;

	//Cuadrado//
	cuadrado.PushBack({ 174,256,12,12 });
	cuadrado.PushBack({ 186,256,12,12 });
	cuadrado.speed = 0.05f;

	//Luz Azul//
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 13);
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 13);
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 13);
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 13);
	luzAzul.speed = 0.2f;

	//Cartel Azul//
	cartelAzul.PushBack({ 556,12,24,131 });
	cartelAzul.PushBack({ 580,12,24,131 });
	cartelAzul.speed = 0.1f;


	//Blanco//
	blanco.PushBack({ 556,0,16,12 });
	blanco.PushBack({ 572,0,16,12 });
	blanco.speed = 0.1f;

	indicator.rect.x = 0;
	indicator.rect.y = 96;
	indicator.rect.h = 16;
	indicator.rect.w = 100;

	timeup.rect.x = 0;
	timeup.rect.y = 129;
	timeup.rect.w = 104;
	timeup.rect.h = 16;

	nthng.PushBack({ 120,23,104,16 }, 0, 0, 30);
	nthng.speed = 0.15f;

	winp1.PushBack({ 0,40,116,40 }, 0, 0, 30);
	winp1.speed = 0.15f;

	winp2.PushBack({ 0,0,120,40 }, 0, 0, 30);
	winp2.speed = 0.15f;

	

}

ModuleSceneJohn::~ModuleSceneJohn()
{}


bool ModuleSceneJohn::Start()
{
	inGame = false;	
	onlyonesound = 0;
	App->render->ResetCamera();
	roundcnt = 0;
	current_animation = &nthng;
	first_row = true;
	LOG("Loading lee scene");
	lee_music = App->audio->Load_music("Assets/Audio/Chinatown_ost.ogg");
	indicator_fight = App->textures->Load("Assets/UI_Sprites/indicator_fight.png");
	fightfx = App->audio->Load_effects("Assets/Audio/FX/Fight.wav");
	first_round = App->audio->Load_effects("Assets/Audio/FX/Round1.wav");
	second_round = App->audio->Load_effects("Assets/Audio/FX/Round2.wav");
	last_round = App->audio->Load_effects("Assets/Audio/FX/LastRound.wav");
	winfx = App->audio->Load_effects("Assets/Audio/FX/win.wav");
	if ((graphics = App->textures->Load("Assets/ChinaTown.png")) == NULL)
	{
		SDL_Log("Unable to load texture from path: /guardian.png");
		return false;
	}
	App->audio->Play_music(lee_music);


	tick1 = SDL_GetTicks();
	//Screen Limits
	//BackPanel = App->collision->AddCollider({ { 0,0,25, SCREEN_HEIGHT },{ 0,0 }, {0, 0} }, COLLIDER_WALL, App->scene_john);
	//FrontPanel = App->collision->AddCollider({ { rect_background.rect.w-25, 0 , 25, SCREEN_HEIGHT },{ 0,0 } ,{ 0, 0 } }, COLLIDER_WALL, App->scene_john);
	//BackPanel->LeftRight = false;
	//FrontPanel->LeftRight = true;

	App->debug->Enable();
	App->player1->Enable();
	App->player2->Enable();
	App->sceneUI->Enable();
	App->input->keyboard_state[SDL_SCANCODE_RETURN] = KEY_IDLE;

	return true;
}


update_status ModuleSceneJohn::Update()
{
	resetstage = false;
	//Render background
	if ((App->render->Blit(graphics, 0, 0, &rect_background)) == false)
	{
		SDL_Log("Unable to [BLIT] texture: texture_background");
		return update_status::UPDATE_STOP;
	}
	//App->input->Paused = false;
	App->render->Blit(graphics, 115, 0, &rojoParpadeo.GetCurrentFrame());

	App->render->Blit(graphics, 0, 0, &rotuloVerde.GetCurrentFrame());

	App->render->Blit(graphics, 88, 0, &radio.GetCurrentFrame());

	App->render->Blit(graphics, 195, 43, &szechu.GetCurrentFrame());

	App->render->Blit(graphics, 55, 59, &morado.GetCurrentFrame());

	App->render->Blit(graphics, 180, 102, &cuadrado.GetCurrentFrame());

	App->render->Blit(graphics, 378, 0, &luzAzul.GetCurrentFrame());

	App->render->Blit(graphics, 433, 7, &cartelAzul.GetCurrentFrame());

	App->render->Blit(graphics, 314, 114, &blanco.GetCurrentFrame());

	//Round mechanics
	if (tick2 - tick1 < 2000) {

		if (rounds_counter == 0)
		{
			resetstage = true;
			indicator.rect.x = 0;
			indicator.rect.y = 96;
			indicator.rect.w = 100;
			indicator.rect.h = 16;
			if (roundcnt == 0)
			{
				App->audio->Play_chunk(first_round);
				roundcnt++;
				
			}
			App->render->Blit(indicator_fight, (SCREEN_WIDTH / 2) - 50, (SCREEN_HEIGHT / 2) - 8, &indicator, 0,1,false);
		}
		if (rounds_counter == 1)
		{
			resetstage = true;
			indicator.rect.x = 0;
			indicator.rect.y = 80;
			indicator.rect.w = 104;
			indicator.rect.h = 16;
			if (roundcnt == 0)
			{

				App->audio->Play_chunk(second_round);
				roundcnt++;
			}
			App->render->Blit(indicator_fight, (SCREEN_WIDTH / 2) - 50, (SCREEN_HEIGHT / 2) - 8, &indicator, 0,1,false);
		}
		if (rounds_counter >1)
		{
			resetstage = true;
			indicator.rect.x = 0;
			indicator.rect.y = 145;
			indicator.rect.w = 168;
			indicator.rect.h = 16;
			if (roundcnt == 0)
			{
				App->audio->Play_chunk(last_round);
				roundcnt++;
			}
			App->render->Blit(indicator_fight, (SCREEN_WIDTH / 2) - 85, (SCREEN_HEIGHT / 2) - 30, &indicator, 0,1,false);
		}
	}

	if (tick2 - tick1>2300 && tick2 - tick1 < 4000) {

		if (first_row == true)
		{
			App->audio->Play_chunk(fightfx);
		}
		indicator.rect.x = 0;
		indicator.rect.y = 113;
		indicator.rect.h = 16;
		indicator.rect.w = 80;
		App->render->CameraLimitL->type = COLLIDER_WALL;
		App->render->CameraLimitR->type = COLLIDER_WALL;
		App->render->Blit(indicator_fight, (SCREEN_WIDTH / 2) - 40, (SCREEN_HEIGHT / 2) - 8, &indicator, 0,1,false);
		first_row = false;
		
		App->input->Paused = false;
		if (!inGame) {
			App->player1->last_input = IN_JUMP_BACKWARD;
			App->player2->last_input = IN_JUMP_BACKWARD;
		}
		inGame = true;
		
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
			if (onlyonesound == 0)
			{
				App->audio->Play_chunk(winfx);
				onlyonesound++;
			}
			
			current_animation = &winp2;
		}

		if (App->player2->Player_Health_Value_p2 > App->player1->Player_Health_Value_p1)
		{
			if (onlyonesound == 0)
			{
				App->audio->Play_chunk(winfx);
				onlyonesound++;
			}
			current_animation = &winp1;
		}

		App->player1->CheckHealth(*App->player2);
		App->player2->CheckHealth(*App->player1);

		App->render->Blit(indicator_fight, (SCREEN_WIDTH / 2) - 50, (SCREEN_HEIGHT) / 2 - 8, &timeup, 0,1,false);
		App->render->Blit(indicator_fight, 145, 45, &current_animation->GetCurrentFrame(), 0,1,false);
		if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 1)
		{
			if (App->player2->p1_win < 2 && App->player1->p2_win < 2)
			{
				App->fade->FadeToBlack(App->scene_john, App->scene_john);
			}
			else
			{
				App->fade->FadeToBlack(App->scene_john, App->scene_congratz);
			}
		}

	}

	if (App->player2->win_check == true)
	{
		if (onlyonesound == 0)
		{
			App->audio->Play_chunk(winfx);
			onlyonesound++;
		}
		current_animation = &winp1;

		App->input->Paused = true;

		if (App->player1->isJumping != true)
		{
			//App->player1->current_state = ST_IDLE;
			//App->player1->last_input = IN_UNKNOWN;
		}

		if (App->player2->isJumping != true)
		{
			//App->player2->current_state = ST_IDLE;
			//App->player2->last_input = IN_UNKNOWN;
		}
		App->render->Blit(indicator_fight, 145, 65, &current_animation->GetCurrentFrame(), 0,1,false);
		if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 1)
		{
			if (App->player2->p1_win < 2)
			{

				App->fade->FadeToBlack(App->scene_john, App->scene_john);
			}
			else
			{
				App->fade->FadeToBlack(App->scene_john, App->scene_congratz);
			}
		}
	}

	if (App->player1->win_check == true)
	{
		if (onlyonesound == 0)
		{
			App->audio->Play_chunk(winfx);
			onlyonesound++;
		}
		current_animation = &winp2;

		App->input->Paused = true;

		if (App->player2->isJumping != true)
		{
			//App->player2->current_state = ST_IDLE;
			//App->player2->last_input = IN_UNKNOWN;
		}

		if (App->player1->isJumping != true)
		{
			//App->player1->current_state = ST_IDLE;
			//App->player1->last_input = IN_UNKNOWN;
		}


		App->render->Blit(indicator_fight, 145, 65, &current_animation->GetCurrentFrame(), 0,1,false);
		if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 1)
		{
			if (App->player1->p2_win < 2)
			{
				App->fade->FadeToBlack(App->scene_john, App->scene_john);
			}
			else
			{
				App->fade->FadeToBlack(App->scene_john, App->scene_congratz);
			}
		}
	}

	tick2 = SDL_GetTicks();
	return UPDATE_CONTINUE;
}

bool ModuleSceneJohn::CleanUp()
{
	if (FrontPanel && BackPanel) 
	{
		FrontPanel->to_delete = true;
		BackPanel->to_delete = true;
	}
	App->sceneUI->Disable();
	App->audio->Unload_music(lee_music);
	App->audio->Unload_effects(fightfx);
	App->audio->Unload_effects(first_round);
	App->audio->Unload_effects(second_round);
	App->audio->Unload_effects(last_round);
	App->audio->Unload_effects(winfx);
	App->textures->Unload(graphics);
	App->textures->Unload(indicator_fight);
	App->player1->Disable();
	App->player2->Disable();

	App->sceneUI->time_over = false;
	App->player1->win_check = false;
	App->player2->win_check = false;
	if (current_animation != &nthng && current_animation!=nullptr)
	{
		rounds_counter++;
	}
	LOG("Unloading john stage");


	App->render->CameraLimitL->type = COLLIDER_NONE;
	App->render->CameraLimitR->type = COLLIDER_NONE;

	return true;
}