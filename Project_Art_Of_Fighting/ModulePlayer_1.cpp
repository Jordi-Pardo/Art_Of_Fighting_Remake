
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleDebug.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"
#include "John.h"
#include "ModuleCharacter_Selection.h"
#include "ModuleSlowdown.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer_1::ModulePlayer_1()
{


	for (int i = 0; i < 3; i++)
	{
		HurtColliders[i] = nullptr;
	}

	pivotRect.rect = { 0,0,10,10 };


}

ModulePlayer_1::~ModulePlayer_1()
{}

// Load assets
bool ModulePlayer_1::Start()
{

	App->input->joystick_up_p1 = false;
	App->input->joystick_down_p1 = false;
	App->input->joystick_left_p1 = false;
	App->input->joystick_right_p1 = false;
	App->input->joystick_left_repeat_p1 = false;
	App->input->joystick_right_repeatp1 = false;

	App->input->gamepad01.A = BUTTON_IDLE;
	App->input->gamepad02.A = BUTTON_IDLE;
	App->input->gamepad01.B = BUTTON_IDLE;
	App->input->gamepad02.B = BUTTON_IDLE;

	last_input = IN_UNKNOWN;
	koukenenabled = false;
	slowdownDuration = 5;
	//if (App->character_selection->IsEnabled()) { //no entra a la condicio fent que peti, ho he hagut de comentar
		if (App->character_selection->SELECTOR_1 == 1) {
			App->player1->character = new John(2);
		}
		else if (App->character_selection->SELECTOR_1 == 2) {
			App->player1->character = new John(1);
		}
	


 
	character->Start();
	shadow_animation = &character->shadow;
	current_animation = &character->idle;
	pivot_player.x = 130;
	pivot_player.y = 150;
	Player_Health_Value_p1 = 126;
	Player_Spirit_Value_p1 = 0;
	LOG("Loading player textures");
	bool ret = true;

	pivotTexture = App->textures->Load("Assets/red_square.png"); // arcade version


	player_collider = App->collision->AddCollider({ { pivot_player.x,pivot_player.y,70,109 },{ 0,0 },{ 0, 0 } }, COLLIDER_PLAYER_COLLISION, App->player1);
	HurtColliders[0] = App->collision->AddCollider({ { 0,0,50,50 },{ 0,0 },{ 0,0 } }, COLLIDER_PLAYER_HURT, App->player1);
	HurtColliders[1] = App->collision->AddCollider({ { 0,0,50,50 },{ 0,0 },{ 0,0 } }, COLLIDER_PLAYER_HURT, App->player1);
	HurtColliders[2] = App->collision->AddCollider({ { 0,0,50,50 },{ 0,0 },{ 0,0 } }, COLLIDER_PLAYER_HURT, App->player1);
	HitCollider = App->collision->AddCollider({ { 50,50,50,50 },{ 0,0 },{ 0,0 } }, COLLIDER_PLAYER_HIT,App->player1);
	HitCollider->Enabled = false;
	Side = 1;

	tick1 = SDL_GetTicks();
	Enemy = App->player2;
	return ret;
}


// Update: draw background
update_status ModulePlayer_1::Update()
{
	speed = 2;

	states(speed);


//CONTROLLER
		//Move right

		if (App->input->joystick_right_p1) {
			last_input = IN_RIGHT_DOWN;
			if (Side == 1) {
				isClose = false;
			}
		}
		else if (Side == 2) {
			isClose = false;
		}

		if (App->input->joystick_left_p1) {
			last_input = IN_LEFT_DOWN;
			if (Side == 2) {
				isClose = false;
			}
		}
		else if (Side == 1) {
				isClose = false;
			
		}

		if (App->input->joystick_up_p1) {
			last_input = IN_JUMP_DOWN;
		}

		//TODO: IMPLEMENT CROUCH WITH CONTROLLER
		if (App->input->joystick_down_p1) {
			last_input = IN_CROUCH_DOWN;
		}
		
		if (App->input->gamepad01.A == BUTTON_DOWN) {
			last_input_attack = last_input = IN_PUNCH;
		}
		else if (App->input->gamepad01.A == BUTTON_REPEAT)
		{
			if (current_state != ST_RECHARGE) {
				if (time < 50) {
					time++;
				}
				else {
					last_input = IN_RECHARGE;
					time = 0;
					LOG("\nIN");
				}
			}
		}
		else if (App->input->gamepad01.A == BUTTON_UP){
			last_input = IN_RECHARGE_UP;
		}

		
		if (App->input->gamepad01.B == BUTTON_DOWN) {
			last_input_attack = last_input = IN_KICK;
		}	
		else if (App->input->gamepad01.B == BUTTON_REPEAT)
		{
			if (current_state != ST_RECHARGE) {
				if (time < 50) {
					time++;
				}
				else {
					last_input = IN_RECHARGE;
					time = 0;
					LOG("\nIN");
				}
			}
		}
		else if (App->input->gamepad01.B == BUTTON_UP) {
			last_input = IN_RECHARGE_UP;
		}
		if (App->input->gamepad01.X == BUTTON_DOWN) {
			switch (last_input_attack)
			{
			case IN_PUNCH: last_input = IN_STRONG_PUNCH; break;
			case IN_KICK: last_input = IN_STRONG_KICK; break;
			}
		}

	

//KEYBOARD
	if (App->input->keyboard_state[SDL_SCANCODE_D] == KEY_REPEAT) {
		last_input = IN_RIGHT_DOWN;
		if (Side == 1) {
			isClose = false;
		}
	}
	if (App->input->keyboard_state[SDL_SCANCODE_D] == KEY_UP)	{
	last_input = IN_RIGHT_UP;
	
		if (Side == 2) {
			isClose = false;
		}
	}

//Move Left
if (App->input->keyboard_state[SDL_SCANCODE_A] == KEY_REPEAT) {
	last_input = IN_LEFT_DOWN;
	if (Side == 2) {
		isClose = false;
	}
}

if (App->input->keyboard_state[SDL_SCANCODE_A] == KEY_UP) {
	last_input = IN_LEFT_UP;
	if (Side == 1) {
		isClose = false;
	}
}

//Crouch
if (App->input->keyboard_state[SDL_SCANCODE_S] == KEY_REPEAT) last_input = IN_CROUCH_DOWN;
if (App->input->keyboard_state[SDL_SCANCODE_S] == KEY_UP)
{
	last_input = IN_CROUCH_UP;
	character->crouch.ResetCurrentFrame();
}

//Punch weak
if (App->input->keyboard_state[SDL_SCANCODE_T] == KEY_DOWN) last_input_attack = last_input = IN_PUNCH;

else if (App->input->keyboard_state[SDL_SCANCODE_T] == KEY_REPEAT)
{	
	if (current_state != ST_RECHARGE) {
		if (time < 50) {
			time++;
		}
		else {
			last_input = IN_RECHARGE;
			time = 0;
			LOG("\nIN");
		}
	}
}
if (App->input->keyboard_state[SDL_SCANCODE_T] == KEY_UP) last_input = IN_RECHARGE_UP;

//kick weak
if (App->input->keyboard_state[SDL_SCANCODE_R] == KEY_DOWN)	last_input_attack= last_input = IN_KICK;
else if (App->input->keyboard_state[SDL_SCANCODE_R] == KEY_REPEAT)
{
	if (current_state != ST_RECHARGE) {
		if (time < 50) {
			time++;
		}
		else {
			last_input = IN_RECHARGE;
			time = 0;
			LOG("\nIN");
		}
	}
}
if (App->input->keyboard_state[SDL_SCANCODE_R] == KEY_UP) last_input = IN_RECHARGE_UP;

//Ko'ou Ken
if (App->input->keyboard_state[SDL_SCANCODE_F] == KEY_DOWN && Player_Spirit_Value_p1 - 26 >= 0) {
	last_input = IN_KOOU_KEN;
}

//Jump
if (App->input->keyboard_state[SDL_SCANCODE_W] == KEY_DOWN) {
	last_input = IN_JUMP_DOWN;
}

//STRONG attack
if (App->input->keyboard_state[SDL_SCANCODE_G] == KEY_DOWN) {
	switch (last_input_attack)
	{
	case IN_PUNCH: last_input = IN_STRONG_PUNCH; break;
	case IN_KICK: last_input = IN_STRONG_KICK; break;
	}
}

//Taunt
if (App->input->keyboard_state[SDL_SCANCODE_Y] == KEY_DOWN || App->input->gamepad01.Y == BUTTON_DOWN)
{
	last_input = IN_TAUNT;
	
}

//win try
if (App->input->keyboard_state[SDL_SCANCODE_1] == KEY_DOWN) last_input = IN_WIN;
//defeat try
if (App->input->keyboard_state[SDL_SCANCODE_2] == KEY_DOWN) last_input = IN_DEFEAT;
//damage try
if (App->input->keyboard_state[SDL_SCANCODE_9] == KEY_DOWN) last_input = IN_DAMAGE_IN_AIR;
//ultrakick try
if (App->input->keyboard_state[SDL_SCANCODE_V] == KEY_DOWN && Player_Spirit_Value_p1 - 26 >= 0) {
	last_input = IN_ULTRA_KICK;
}

//Check duration of animation and reset state when it finishes
if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 1 && current_state != ST_IDLE && current_state != ST_CROUCH && current_state != ST_RECHARGE)
{


	if (current_animation == &character->recover) {
		last_input = IN_RECOVER_FINISH;
		if (App->player2->Player_Health_Value_p2 == 0)
		{
			last_input = IN_DEFEAT;
		}
	}
	else if (current_animation == &character->air_damage) {
		last_input = IN_FALL_AIR;
	}
	else if (current_animation == &character->air_damage_fall) {
		last_input = IN_BOUNCE;
	}
	else
	{
		last_input = IN_ATTACK_FINISH;
		HitCollider->Enabled = false;
		HurtColliders[0]->Enabled = true;
		HurtColliders[1]->Enabled = true;
		HurtColliders[2]->Enabled = true;
		player_collider->Enabled = true;
		character->isBlocking = false;

	}
}




//DEBUG CONTROLS, Direct win/lose when pressing I or O
if (App->input->keyboard_state[SDL_SCANCODE_O] == KEY_DOWN && player_collider->type == COLLIDER_NONE && !App->fade->IsFading)
{
	Deal_Damage(*App->player2, 200);
}

	//God Mode
	if (App->input->keyboard_state[SDL_SCANCODE_F5] == KEY_DOWN && player_collider->type == COLLIDER_PLAYER_COLLISION)
	{

		player_collider->type = COLLIDER_NONE;
		App->player2->player_collider->type = COLLIDER_NONE;
		timer = SDL_GetTicks();
		LOG("\nGod Mode ON");
	}
	if (App->input->keyboard_state[SDL_SCANCODE_F5] == KEY_DOWN && player_collider->type == COLLIDER_NONE && SDL_GetTicks() != timer)
	{

		player_collider->type = COLLIDER_PLAYER_COLLISION;
		App->player2->player_collider->type = COLLIDER_PLAYER_COLLISION;
		LOG("\nGod Mode OFF");
	}

	//ViewPoint
	if (player_collider->rect.x < App->player2->player_collider->rect.x)
	{
		Side = 1;
	}
	else
	{
		Side = 2;
	}

	if ((App->player2->current_state == ST_STANDING_PUNCH || App->player2->current_state == ST_CROUCH_PUNCH || App->player2->current_state == ST_CROUCH_KICK) && isClose) {
		last_input = IN_BLOCKING;
		character->isBlocking = true;
	}

//4 seconds without moving
tick2 = SDL_GetTicks();
if (tick2 - tick1 > 4000 && App->sceneUI->time_over == false && App->player1->win_check != true && App->player2->win_check != true)
{
	App->input->Paused = false;
}


// Draw everything --------------------------------------
RectSprites r = current_animation->GetCurrentFrame();
RectSprites shadow = shadow_animation->GetCurrentFrame();

if (App->render->spriteShaking) {
	App->render->UpdateSpriteShake(&r.offset);
}

player_collider->rect.x = pivot_player.x;
player_collider->rect.h = 90;
player_collider->rect.w = 32;

if ((App->input->keyboard_state[SDL_SCANCODE_A] == KEY_REPEAT || App->input->joystick_left_p1) && Side == 1) {
	int num = pivot_player.x - App->player2->GetPosition().x;
	if (num < 0) {
		num *= -1;
	}
	//SDL_Log("%d", num);
	if (num < 150){
		isClose = true;
		//LOG("CLOSE");
	}
	else {
		isClose = false;
	}
}else if ((App->input->keyboard_state[SDL_SCANCODE_D] == KEY_REPEAT || App->input->joystick_right_p1) && Side == 2) {
	int num = pivot_player.x - App->player2->GetPosition().x;
	if (num < 0) {
		num *= -1;
	}
	//SDL_Log("%d", num);
	if (num < 150){
		isClose = true;
		//LOG("CLOSE");
	}
	else {
		isClose = false;
	}
}
if (current_state == ST_STANDING_BLOCKED) {
	iPoint p = character->exitBlock.GetDisplacementFrame();
	if (Side == 1) {
		pivot_player += p;
	}
	else {
		pivot_player -= p;

	}
	if (character->exitBlock.GetDisplacementFramePos() == character->exitBlock.GetLastFrame() - 1)
	{
		character->exitBlock.ResetDisplacement();
	}
}
if (current_state == ST_IDLE_TO_DAMAGE) {
	iPoint p = character->pose_idle_receive_standing_punch_kick_plus_jump_punch.GetDisplacementFrame();
	if (Side == 1) {
		pivot_player += p;
	}
	else {
		pivot_player -= p;

	}
	if (character->pose_idle_receive_standing_punch_kick_plus_jump_punch.GetDisplacementFramePos() == character->pose_idle_receive_standing_punch_kick_plus_jump_punch.GetLastFrame() - 1)
	{
		character->pose_idle_receive_standing_punch_kick_plus_jump_punch.ResetDisplacement();
	}
}
if (current_state == ST_IDLE_TO_DAMAGE_LONG) {
	iPoint p = character->pose_idle_receive_standing_punch_kick_plus_jump_punch_long.GetDisplacementFrame();
	if (Side == 1) {
		pivot_player += p;
	}
	else {
		pivot_player -= p;

	}
	if (character->pose_idle_receive_standing_punch_kick_plus_jump_punch_long.GetDisplacementFramePos() == character->pose_idle_receive_standing_punch_kick_plus_jump_punch_long.GetLastFrame() - 1)
	{
		character->pose_idle_receive_standing_punch_kick_plus_jump_punch_long.ResetDisplacement();
	}
}


if (current_state == ST_DAMAGE_IN_AIR) {
	iPoint p = character->air_damage.GetDisplacementFrame();
	pivot_player += p;
	if (character->air_damage.GetDisplacementFramePos() == character->air_damage.GetLastFrame() - 5)
	{
		character->air_damage.ResetDisplacement();
	}
}

if (current_state == ST_FALL_FROM_AIR) {
	iPoint p = character->air_damage_fall.GetDisplacementFrame();
	if (pivot_player.y < 200) {
		pivot_player += p;
	}else{
		last_input = IN_BOUNCE;

	}
	if (character->air_damage_fall.GetDisplacementFramePos() == character->air_damage_fall.GetLastFrame() - 1)
	{
		character->air_damage_fall.ResetDisplacement();
	}
}

	if (current_state == ST_NEUTRAL_JUMP || current_state == ST_NEUTRAL_JUMP_PUNCH || current_state == ST_FALL || current_state == ST_NEUTRAL_JUMP_KICK)
	{
		isJumping = true;
		iPoint p = character->jump.GetDisplacementFrame();
		pivot_player += p;
		if (p.y > 0)
		{
			//Falling
			player_collider->Enabled = true;
		}
		if (character->jump.GetDisplacementFramePos() == character->jump.GetLastFrame() - 5)
		{
			App->audio->Play_chunk(character->fallfx);
			character->jump.ResetDisplacement();
			pivot_player.y = 150;
			last_input = IN_RECOVER;
			isJumping = false;
		}

	}

	if (current_state == ST_FORWARD_JUMP || current_state == ST_FORWARD_JUMP_PUNCH || current_state == ST_FORWARD_FALL || current_state == ST_FORWARD_JUMP_KICK)
	{
		isJumping = true;
		iPoint p = character->jump_forward.GetDisplacementFrame();
		pivot_player += p;
		if (p.y > 0)
		{
			//Falling
			player_collider->Enabled = true;
		}
		if (character->jump_forward.GetDisplacementFramePos() == character->jump_forward.GetLastFrame() - 5)
		{
			App->audio->Play_chunk(character->fallfx);
			character->jump_forward.ResetDisplacement();
			pivot_player.y = 150;
			last_input = IN_RECOVER;
			isJumping = false;
		}
	}


	if (current_state == ST_BACKWARD_JUMP || current_state == ST_BACKWARD_JUMP_PUNCH || current_state == ST_BACKWARD_FALL || current_state == ST_BACKWARD_JUMP_KICK)
	{
		isJumping = true;
		iPoint p = character->jump_backward.GetDisplacementFrame();
		pivot_player += p;
		if (p.y > 0)
		{
			//Falling
			player_collider->Enabled = true;
		}
		if (character->jump_backward.GetDisplacementFramePos() == character->jump_backward.GetLastFrame() - 5)
		{
			App->audio->Play_chunk(character->fallfx);
			character->jump_backward.ResetDisplacement();
			pivot_player.y = 150;
			last_input = IN_RECOVER;
			isJumping = false;
		}

	}

	//Waits defeat to end
	if (current_state == ST_DEFEAT && current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 1)
	{
		App->input->Paused = true;
		App->player2->last_input = IN_WIN;
	}
	if (current_state == ST_ULTRA_KICK && current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 3)
	{
		App->audio->Play_chunk(character->punch1fx);
	}

	if (Side == 2) {

		App->render->Blit(character->graphics, pivot_player.x + shadow.offset_reverse.x,145 + shadow.offset_reverse.y, &shadow, 1, Side);
		App->render->Blit(character->graphics, pivot_player.x + r.offset_reverse.x, pivot_player.y + r.offset_reverse.y, &r, 1, Side);
	}
	else if (Side == 1)
	{
		App->render->Blit(character->graphics, pivot_player.x + shadow.offset.x,145 + shadow.offset.y, &shadow, 1, Side, true);
		App->render->Blit(character->graphics, pivot_player.x + r.offset.x, pivot_player.y + r.offset.y, &r, 1, Side,true);
		

	}



	if (isJumping)
	{
		player_collider->SetPos(pivot_player.x - character->colliderOffsetX, pivot_player.y - 45);

	}
	else if (current_state == ST_CROUCH || current_state == ST_CROUCH_PUNCH || current_state == ST_CROUCH_KICK)
	{
		player_collider->rect.h = 65;
		player_collider->SetPos(pivot_player.x - character->colliderOffsetX, pivot_player.y);
	}
	else
	{
		player_collider->rect.h = 90;
		player_collider->SetPos(pivot_player.x - character->colliderOffsetX, pivot_player.y - 25);
	}

	for (int i = 0; i < 3; i++)
	{
		SDL_Rect rect[3];
		rect[i] = r.hurtColliders[i];
		if (Side == 2) {
			rect[0].x = rect[0].x + 5;
			rect[1].x = rect[1].x + 5;
			rect[2].x = rect[2].x + 10;

		}
		HurtColliders[i]->SetRect(rect[i], current_animation->damage, pivot_player);
	}
	if (HitCollider != nullptr)
	{
		iPoint newPos = pivot_player;
		if (Side == 2) {
			newPos.x = newPos.x + 60;
		}
		HitCollider->SetRect(r.hitCollider, current_animation->damage, newPos, Side);
	}


	//TODO: Delete this line and move it to generic place
	if (character->CheckCombos(App->player1, nullptr) != IN_EMPTY)
	{
		last_input = character->CheckCombos(App->player1, nullptr);
	}


	return UPDATE_CONTINUE;
}

bool ModulePlayer_1::CleanUp()
{
	App->textures->Unload(pivotTexture);
	if (character != nullptr) {
		character->CleanUp();
		delete character;
		character = nullptr;
	}
	if (player_collider != nullptr)
	{
		player_collider->to_delete = true;
	}
	if (HitCollider != nullptr)
	{
		HitCollider->to_delete = true;
	}

	for (int i = 0; i < 3; i++)
	{
		if (HurtColliders[i] != nullptr)
		{
			HurtColliders[i]->to_delete = true;
		}
	}

	LOG(" - ModulePlayer CleanUp");
	return true;
}

void ModulePlayer_1::OnCollision(Collider * c1, Collider * c2)
{

	//Camera limits
	//TODO: Player shakes when is pussed to move a wall by other player
	//Is Player coliding with wall?
	if (c2->type == COLLIDER_WALL)
	{
		//Camera is not under nor over the limit
		if (-App->render->camera.x < 0)
			App->render->camera.x = 0;

		if (-App->render->camera.x > App->render->CurrentSceneLenght - 44 && WIN_FULLSCREEN_DESKTOP == 0)
			App->render->camera.x = -(App->render->CurrentSceneLenght - 44);
		if (-App->render->camera.x > ((App->render->CurrentSceneLenght * App->render->zoomValue) - 385) && WIN_FULLSCREEN_DESKTOP == 1)
			App->render->camera.x = -((App->render->CurrentSceneLenght * App->render->zoomValue) - 385);


		//Coliding with left side of the camera?
		if (c2->LeftRight == false)
		{
			//Move camera
			if (-App->render->camera.x > 0)
				App->render->camera.x += App->render->speed * 2;
			//Limit player inside camera
			pivot_player.x = c2->rect.x + c2->rect.w + (pivot_player.x - player_collider->rect.x);
		}

		if (c2->LeftRight == true)
		{
			//Move camera and limit player
			App->render->camera.x -= App->render->speed * 2;
			pivot_player.x = c2->rect.x + (pivot_player.x - player_collider->rect.x) - player_collider->rect.w;
		}
	}
	
	////Am I coliding with an enemy?
	//if (c2->type == COLLIDER_ENEMY_COLLISION && (c1->Enabled && c2->Enabled))
	//{

	//	//Only if is moving
	//	if (current_state != ST_IDLE)
	//	{
	//		//When can you move the enemy? I'm coliding from the right?
	//		if (player_collider->rect.x + player_collider->rect.w - 5 < Enemy->player_collider->rect.x)
	//		{
	//			if (Enemy->player_collider->rect.x + Enemy->player_collider->rect.w < App->render->CameraLimitR->rect.x)
	//			{
	//				//Am i entering to the enemy by the left?
	//				//eNEMY REPELED BY PLAYER
	//				Enemy->pivot_player.x = player_collider->rect.x + player_collider->rect.w + (Enemy->pivot_player.x - Enemy->player_collider->rect.x);
	//			}
	//			else
	//			{
	//				//PLAYED REPELED BY ENEMY ON WALL COLISION
	//				pivot_player.x = Enemy->pivot_player.x - (Enemy->pivot_player.x - Enemy->player_collider->rect.x) - ((player_collider->rect.x + player_collider->rect.w) - pivot_player.x);
	//			}
	//		}
	//		else
	//		{
	//			if (Enemy->player_collider->rect.x > App->render->CameraLimitL->rect.x + App->render->CameraLimitL->rect.w)
	//			{
	//				//Am i entering to the enemy by the RIGHT?
	//				//PLAYER PUSHING ENEMY BACKWARDS
	//				Enemy->pivot_player.x = pivot_player.x - (pivot_player.x - player_collider->rect.x) - ((Enemy->player_collider->rect.x + Enemy->player_collider->rect.w) - Enemy->pivot_player.x);
	//			}
	//			else
	//			{
	//				pivot_player.x = Enemy->player_collider->rect.x + Enemy->player_collider->rect.w + (pivot_player.x - player_collider->rect.x);
	//			}
	//		}
	//	}


	//	LOG("");
	//}

	//New Player Collisions
	if (c2->type == COLLIDER_ENEMY_COLLISION && (c1->Enabled && c2->Enabled))
	{
		//Coliding from the right
		if (c2->rect.x >= player_collider->rect.x)
		{
			App->player2->pivot_player.x += 2;
		}
		//Coliding from the left
		if (c2->rect.x <= player_collider->rect.x)
		{
			App->player2->pivot_player.x -= 2;
		}

	}





	//Hit Detection
	if (c2->type == COLLIDER_ENEMY_HIT && (c2->Enabled && c1->Enabled))
	{
		if (!App->player1->character->isBlocking) {
			int offsetX = 0;
			Deal_Damage(*App->player2, c2->ColliderDamage);
			if (Side == 2) {
				offsetX = 35;
			}
			App->particles->AddParticle(App->particles->starhit, c2->rect.x + offsetX, c2->rect.y, COLLIDER_NONE, 0, 0, Side, RYO);
			c2->Enabled = false;
		}
		else if (App->player1->character->isBlocking) {
			int offsetX = 0;
			if (Side == 2) {
				offsetX = 35;
			}
			c2->Enabled = false;
			LOG("\nBLOCKED\n");
			App->particles->AddParticle(App->particles->blue_starhit, c2->rect.x+ offsetX, c2->rect.y, COLLIDER_NONE, 0, 0, Side,JOHN);
			last_input = IN_BLOCKED;

		}

	}


}

player_state ModulePlayer_1::ControlStates()
{
	static player_state state = ST_IDLE;

	character->AddInput(last_input, SDL_GetTicks());

	switch (current_state)
	{
	case ST_IDLE:
		switch (last_input)
		{
		case IN_TEST: state = ST_TEST; break;
		case IN_UNKNOWN: state = ST_IDLE; break;
		case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
		case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
		case IN_JUMP_DOWN: state = ST_NEUTRAL_JUMP;	 break;
		case IN_PUNCH: state = ST_STANDING_PUNCH; break;
		case IN_KICK: state = ST_STANDING_KICK; break;
		case IN_KOOU_KEN: state = ST_KOOU_KEN; break;
		case IN_CROUCH_DOWN: state = ST_CROUCH; break;
		case IN_STRONG_PUNCH: state = ST_STRONG_PUNCH; break;
		case IN_STRONG_KICK: state = ST_STRONG_KICK; break;
		case IN_WIN: state = ST_WIN; break;
		case IN_DEFEAT: state = ST_DEFEAT; break;
		case IN_RECEIVE_DAMAGE: state = ST_IDLE_TO_DAMAGE; break;
		case IN_RECEIVE_DAMAGE_LONG: state = ST_IDLE_TO_DAMAGE_LONG; break;
		case IN_TAUNT: state = ST_TAUNT; break;
		case IN_ULTRA_KICK:state = ST_ULTRA_KICK; break;
		case IN_RECHARGE : state = ST_RECHARGE; break;
		case IN_JUMP_BACKWARD: state = ST_BACKWARD_JUMP; break;
		}
		break;
	case ST_WALK_FORWARD:
		switch (last_input)
		{
		case IN_RIGHT_UP: state = ST_IDLE; break;
		case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
		case IN_PUNCH: state = ST_STANDING_PUNCH; break;
		case IN_KICK: state = ST_STANDING_KICK; break;
		case IN_KOOU_KEN: state = ST_KOOU_KEN; break;
		case IN_JUMP_DOWN: state = ST_FORWARD_JUMP; break;
		case IN_UNKNOWN: state = ST_IDLE; break;
		case IN_CROUCH_DOWN: state = ST_CROUCH; break;
		case IN_RECEIVE_DAMAGE: state = ST_IDLE_TO_DAMAGE; break;
		case IN_RECEIVE_DAMAGE_LONG: state = ST_IDLE_TO_DAMAGE_LONG; break;
		case IN_BLOCKING: state = ST_STANDING_BLOCK; break;
		case IN_TAUNT: state = ST_TAUNT; break;
		case IN_RECHARGE: state = ST_RECHARGE; break;
		case IN_STRONG_PUNCH: state = ST_STRONG_PUNCH; break;
		case IN_STRONG_KICK: state = ST_STRONG_KICK; break;
		case IN_WIN: state = ST_WIN; break;
		case IN_DEFEAT: state = ST_DEFEAT; break;
		case IN_ULTRA_KICK:state = ST_ULTRA_KICK; break;
		}
		break;
	case ST_WALK_BACKWARD:
		switch (last_input)
		{
		case IN_LEFT_UP: state = ST_IDLE; break;
		case IN_RIGHT_DOWN: state = ST_IDLE; break;
		case IN_PUNCH: state = ST_STANDING_PUNCH; break;
		case IN_KICK: state = ST_STANDING_KICK; break;
		case IN_KOOU_KEN: state = ST_KOOU_KEN; break;
		case IN_JUMP_DOWN: state = ST_BACKWARD_JUMP; break;
		case IN_UNKNOWN: state = ST_IDLE; break;
		case IN_CROUCH_DOWN: state = ST_CROUCH; break;
		case IN_RECEIVE_DAMAGE: state = ST_IDLE_TO_DAMAGE; break;
		case IN_RECEIVE_DAMAGE_LONG: state = ST_IDLE_TO_DAMAGE_LONG; break;
		case IN_BLOCKING: state = ST_STANDING_BLOCK; break;
		case IN_TAUNT: state = ST_TAUNT; break;
		case IN_RECHARGE: state = ST_RECHARGE; break;
		case IN_STRONG_PUNCH: state = ST_STRONG_PUNCH; break;
		case IN_STRONG_KICK: state = ST_STRONG_KICK; break;
		case IN_WIN: state = ST_WIN; break;
		case IN_DEFEAT: state = ST_DEFEAT; break;
		case IN_ULTRA_KICK:state = ST_ULTRA_KICK; break;
		}
		break;
	case ST_STANDING_PUNCH:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_IDLE; break;
		case IN_RECEIVE_DAMAGE: state = ST_IDLE_TO_DAMAGE; break;
		case IN_RECEIVE_DAMAGE_LONG: state = ST_IDLE_TO_DAMAGE_LONG; break;
		case IN_KOOU_KEN: state = ST_KOOU_KEN; break;
		}
		break;

	case ST_STANDING_KICK:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_IDLE; break;
		case IN_RECEIVE_DAMAGE: state = ST_IDLE_TO_DAMAGE; break;
		case IN_RECEIVE_DAMAGE_LONG: state = ST_IDLE_TO_DAMAGE_LONG; break;
		case IN_ULTRA_KICK:state = ST_ULTRA_KICK; break;
		}
		break;
	case ST_STRONG_PUNCH:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_IDLE; break;
		}
		break;	
	case ST_STRONG_KICK:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_IDLE; break;
		}
		break;
	case ST_NEUTRAL_JUMP:
		switch (last_input)
		{
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_PUNCH: state = ST_NEUTRAL_JUMP_PUNCH; break;
		case IN_KICK: state = ST_NEUTRAL_JUMP_KICK; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_RECEIVE_DAMAGE: state = ST_DAMAGE_IN_AIR; break;
		}
		break;
	case ST_FORWARD_JUMP:
		switch (last_input)
		{
		case IN_PUNCH: state = ST_FORWARD_JUMP_PUNCH; break;
		case IN_KICK: state = ST_FORWARD_JUMP_KICK; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_RECEIVE_DAMAGE: state = ST_DAMAGE_IN_AIR; break;
		}
		break;
	case ST_FORWARD_JUMP_PUNCH:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_FORWARD_FALL; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_RECEIVE_DAMAGE: state = ST_DAMAGE_IN_AIR; break;
		}
		break;
	case ST_FORWARD_JUMP_KICK:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_FORWARD_FALL; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_RECEIVE_DAMAGE: state = ST_DAMAGE_IN_AIR; break;
		}
		break;
	case ST_BACKWARD_JUMP:
		switch (last_input)
		{
		case IN_PUNCH: state = ST_BACKWARD_JUMP_PUNCH; break;
		case IN_KICK: state = ST_BACKWARD_JUMP_KICK; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_RECEIVE_DAMAGE: state = ST_DAMAGE_IN_AIR; break;
		}
		break;
	case ST_BACKWARD_JUMP_PUNCH:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_BACKWARD_FALL; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_RECEIVE_DAMAGE: state = ST_DAMAGE_IN_AIR; break;
		}
		break;
	case ST_BACKWARD_JUMP_KICK:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_BACKWARD_FALL; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_RECEIVE_DAMAGE: state = ST_DAMAGE_IN_AIR; break;
		}
		break;
	case ST_KOOU_KEN:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_IDLE; break;
		case IN_RECEIVE_DAMAGE: state = ST_IDLE_TO_DAMAGE; break;
		}
		break;
	case ST_NEUTRAL_JUMP_PUNCH:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_FALL; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_RECEIVE_DAMAGE: state = ST_DAMAGE_IN_AIR; break;
		}
		break;
	case ST_NEUTRAL_JUMP_KICK:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_FALL; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_RECEIVE_DAMAGE: state = ST_DAMAGE_IN_AIR; break;
		}
		break;
	case ST_FALL:
		switch (last_input)
		{
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_PUNCH: state = ST_NEUTRAL_JUMP_PUNCH; break;
		case IN_KICK: state = ST_NEUTRAL_JUMP_KICK; break;
		}
		break;
	case ST_FORWARD_FALL:
		switch (last_input)
		{
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_PUNCH: state = ST_FORWARD_JUMP_PUNCH; break;
		case IN_KICK: state = ST_FORWARD_JUMP_KICK; break;
		}
		break;
	case ST_BACKWARD_FALL:
		switch (last_input)
		{
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_PUNCH: state = ST_BACKWARD_JUMP_PUNCH; break;
		case IN_KICK: state = ST_BACKWARD_JUMP_KICK; break;
		}
		break;
	case ST_RECOVER:
		switch (last_input)
		{
		case IN_RECOVER_FINISH: state = ST_IDLE; break;
		case IN_WIN: state = ST_WIN; break;
		case IN_DEFEAT: state = ST_DEFEAT; break;
		}
		break;
	case ST_CROUCH:
		switch (last_input)
		{
		case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
		case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
		case IN_CROUCH_UP: state = ST_IDLE; break;
		case IN_PUNCH: state = ST_CROUCH_PUNCH; break;
		case IN_KICK: state = ST_CROUCH_KICK; break;
		case IN_UNKNOWN: state = ST_IDLE; break;
		case IN_RECEIVE_DAMAGE: state = ST_IDLE_TO_DAMAGE; break;
		case IN_RECEIVE_DAMAGE_LONG: state = ST_IDLE_TO_DAMAGE_LONG; break;
		//case IN_BLOCKING: state = ST_CROUCH_BLOCK; break;
		case IN_WIN: state = ST_WIN; break;
		case IN_DEFEAT: state = ST_DEFEAT; break;
		}
		break;
	case ST_CROUCH_PUNCH:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_CROUCH;  break;
		}
		break;
	case ST_CROUCH_KICK:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_CROUCH;  break;
		}
		break;
	case ST_CROUCH_DAMAGE:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_CROUCH; break;
		}
		break;
	case ST_IDLE_TO_DAMAGE:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_IDLE; break;
		}
		break;
	case ST_IDLE_TO_DAMAGE_LONG:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_IDLE; break;
		}
		break;
	case ST_STANDING_BLOCK:
		switch (last_input)
		{
		case IN_BLOCKED: state = ST_STANDING_BLOCKED; break;
		case IN_ATTACK_FINISH:
			if (Side == 1) {
				state = ST_WALK_BACKWARD;
			}
			else if (Side == 2) {
				state = ST_WALK_FORWARD;
			}
			break;
		}
		break;
	case ST_STANDING_BLOCKED:
		switch (last_input)
		{
		case IN_ATTACK_FINISH:
			if (Side == 1) {
				state = ST_WALK_BACKWARD;
			}
			else if (Side == 2) {
				state = ST_WALK_FORWARD;
			}
			break;
		}
		break;
	case ST_CROUCH_BLOCK:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_CROUCH; break;
		}
		break;

	case ST_WIN:
		switch (last_input)
		{
		case IN_UNKNOWN:
			if (App->scene_john->resetstage == true)
			{
				state = ST_IDLE;
			} break;
		case IN_RECHARGE_UP:
			if (App->scene_john->resetstage == true)
			{
				state = ST_IDLE;
			} break;
		}
		break;

	case ST_DEFEAT:

		switch (last_input)
		{
		case IN_UNKNOWN:
			if (App->scene_john->resetstage == true)
			{
				state = ST_IDLE;
			} break;
		case IN_RECHARGE_UP:
			if (App->scene_john->resetstage == true)
			{
				state = ST_IDLE;
			} break;
		}
		break;
	case ST_TAUNT:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_IDLE; break;
		}
		break;
	case ST_DAMAGE_IN_AIR:
		switch (last_input)
		{
		case IN_FALL_AIR: state = ST_FALL_FROM_AIR; break;
		case IN_DEFEAT: state = ST_FALL_FROM_AIR; break;
		}
		break;	
	case ST_FALL_FROM_AIR:
		switch (last_input)
		{
		case IN_BOUNCE: state = ST_BOUNCE; break;
		case IN_DEFEAT: state = ST_BOUNCE; break;
		}
		break;
	case ST_BOUNCE:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_RECOVER_FROM_AIR; break;
		case IN_DEFEAT: break;
		}
		break;
	case ST_RECOVER_FROM_AIR:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_IDLE; break;
		}
		break;
	case ST_RECHARGE:
		switch (last_input)
		{
		case IN_RECHARGE_UP:state = ST_IDLE; break;
		}
		break;
	case ST_ULTRA_KICK:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_IDLE; break;
		case IN_RECEIVE_DAMAGE: state = ST_IDLE_TO_DAMAGE; break;
		}
		break;

	}
	//SDL_Log("Last input: %d", last_input);
	last_input = IN_UNKNOWN;

	return state;
}
void ModulePlayer_1::states(int speed)
{
	player_state state = ControlStates();

	// Control state
	switch (state)
	{
	case ST_IDLE:
	
		if (rechargeParticle != nullptr && !particleDeleted) {
			App->particles->DeleteLastParticle(rechargeParticle);
			particleDeleted = true;
		}
		current_animation = &character->idle;
		HurtColliders[0]->Enabled = true;
		HurtColliders[1]->Enabled = true;
		HurtColliders[2]->Enabled = true;
		player_collider->Enabled = true;
		//LOG("IDLE");
		break;
	case ST_WALK_FORWARD:
		pivot_player.x += speed;
		if (current_animation != &character->forward && Side == 1)
		{
			character->forward.ResetCurrentFrame();
			current_animation = &character->forward;
		}
		if (current_animation != &character->backward && Side == 2)
		{
			character->backward.ResetCurrentFrame();
			current_animation = &character->backward;
		}
		//LOG("FORWARD");
		break;
	case ST_WALK_BACKWARD:
		pivot_player.x -= speed;
		if (current_animation != &character->backward && Side == 1)
		{
			character->backward.ResetCurrentFrame();
			current_animation = &character->backward;
		}
		if (current_animation != &character->forward && Side == 2)
		{
			character->forward.ResetCurrentFrame();
			current_animation = &character->forward;
		}
		//LOG("BACKWARD");
		break;
	case ST_STANDING_PUNCH:
		if (current_animation != &character->punch)
		{
			punchrandomizer++;
			character->punch.ResetCurrentFrame();
			HitCollider->Enabled = true;
			current_animation = &character->punch;
			if (punchrandomizer % 2 == 0)
			{
				App->audio->Play_chunk(character->punch1fx);
			}
			else
			{
				App->audio->Play_chunk(character->punch2fx);
			}
			App->audio->Play_chunk(character->punchfx);
			App->audio->Play_chunk(character->punchfx);

		}
		//LOG("PUNCH");
		break;
	case ST_STANDING_KICK:
		if (current_animation != &character->kick)
		{
			character->kick.ResetCurrentFrame();
			HitCollider->Enabled = true;
			current_animation = &character->kick;
			App->audio->Play_chunk(character->punch2fx);
			App->audio->Play_chunk(character->kickfx2);
			App->audio->Play_chunk(character->kickfx2);
		}
		LOG("KICK");
		break;
	case ST_STRONG_PUNCH:
			if (current_animation != &character->c_punch)
			{
				character->c_punch.ResetCurrentFrame();
				HitCollider->Enabled = true;
				current_animation = &character->c_punch;
				App->audio->Play_chunk(character->punchfx);
				App->audio->Play_chunk(character->punch1fx);
			}
		LOG("STRONG PUNCH");
		break;
	case ST_STRONG_KICK:
		if (current_animation != &character->c_kick)
		{
			character->c_kick.ResetCurrentFrame();
			HitCollider->Enabled = true;
			current_animation = &character->c_kick;
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
		}
		LOG("STRONG KICK");
		break;
	case ST_NEUTRAL_JUMP:
		if (current_animation != &character->jump)
		{
			character->jump.ResetCurrentFrame();
			character->jump.ResetDisplacement();
			current_animation = &character->jump;
			App->audio->Play_chunk(character->jumpfx);
			player_collider->Enabled = false;
		}
		LOG("NEUTRAL JUMP");
		break;
	case ST_KOOU_KEN:
		if (current_animation != &character->koouKen)
		{
			//App->render->StartCameraShake(10,4.0f);
			character->koouKen.ResetCurrentFrame();
			spiritKouKen = true;
			switch (character->characterType)
			{
			case RYO:
				App->particles->AddParticle(App->particles->pre_koouKen, pivot_player.x, pivot_player.y, COLLIDER_NONE, 50, 0, Side,RYO);
				currentParticle = App->particles->AddParticle(App->particles->koouKen, pivot_player.x - 28, pivot_player.y, COLLIDER_PLAYER_HIT, 600, character->specialDmg, Side,RYO);
				current_animation = &character->koouKen;
				App->audio->Play_chunk(character->kooukenfx);
				break;
			case JOHN:
				currentParticle = App->particles->AddParticle(App->particles->megaSmash, pivot_player.x +35, pivot_player.y - 20, COLLIDER_PLAYER_HIT, 600, character->specialDmg, Side,JOHN);
				current_animation = &character->koouKen;
				App->audio->Play_chunk(character->kooukenfx);
				koukenenabled = true;
				break;
			}
		}
		break;
	case ST_NEUTRAL_JUMP_PUNCH:
		if (current_animation != &character->jumppunch)
		{
			HitCollider->Enabled = true;
			character->jumppunch.ResetCurrentFrame();
			current_animation = &character->jumppunch;
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
			player_collider->Enabled = false;
		}
		LOG("NEUTRAL JUMP PUNCH");
		break;
	case ST_NEUTRAL_JUMP_KICK:
		if (current_animation != &character->jumpkick)
		{
			HitCollider->Enabled = true;
			character->jumpkick.ResetCurrentFrame();
			current_animation = &character->jumpkick;
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
			player_collider->Enabled = false;
		}
		LOG("NEUTRAL JUMP KIcK");
		break;
	case ST_FORWARD_JUMP:
		if (current_animation != &character->jump_forward)
		{
			character->jump_forward.ResetCurrentFrame();
			character->jump_forward.ResetDisplacement();
			current_animation = &character->jump_forward;
			App->audio->Play_chunk(character->jumpfx);
			player_collider->Enabled = false;
		}
		LOG("FORWARD JUMP");
		break;
	case ST_FORWARD_JUMP_KICK:
		if (current_animation != &character->jumpkick)
		{
			character->jumpkick.ResetCurrentFrame();
			HitCollider->Enabled = true;
			current_animation = &character->jumpkick;
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
			player_collider->Enabled = false;
		}
		LOG("FORWARD JUMP KICK");
		break;
	case ST_FORWARD_JUMP_PUNCH:
		if (current_animation != &character->jumppunch)
		{
			HitCollider->Enabled = true;
			character->jumppunch.ResetCurrentFrame();
			current_animation = &character->jumppunch;
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
			player_collider->Enabled = false;
		}
		LOG("FORWARD JUMP PUNCH");
		break;
	case ST_BACKWARD_JUMP:
		if (current_animation != &character->jump_backward)
		{
			character->jump_backward.ResetCurrentFrame();
			character->jump_backward.ResetDisplacement();
			current_animation = &character->jump_backward;
			App->audio->Play_chunk(character->jumpfx);
			player_collider->Enabled = false;
		}
		LOG("BACKWARD JUMP");
		break;
	case ST_BACKWARD_JUMP_PUNCH:
		if (current_animation != &character->jumppunch)
		{
			HitCollider->Enabled = true;
			character->jumppunch.ResetCurrentFrame();
			current_animation = &character->jumppunch;
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
			player_collider->Enabled = false;
		}
		LOG("BACKWARD JUMP PUNCH");
		break;
	case ST_BACKWARD_JUMP_KICK:
		if (current_animation != &character->jumpkick)
		{
			HitCollider->Enabled = true;
			character->jumpkick.ResetCurrentFrame();
			current_animation = &character->jumpkick;
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
			player_collider->Enabled = false;
		}
		LOG("BACKWARD JUMP KICK");
		break;
	case ST_FALL:
		if (current_animation != &character->fall) {
			character->fall.ResetCurrentFrame();
			character->fall.ResetDisplacement();
			current_animation = &character->fall;
			player_collider->Enabled = false;
		}
		LOG("FALL");
		break;
	case ST_FORWARD_FALL:
		if (current_animation != &character->fall) {
			character->fall.ResetCurrentFrame();
			character->fall.ResetDisplacement();
			current_animation = &character->fall;
			player_collider->Enabled = false;
		}
		LOG("FALL");
		break;
	case ST_BACKWARD_FALL:
		if (current_animation != &character->fall) {
			character->fall.ResetCurrentFrame();
			character->fall.ResetDisplacement();
			current_animation = &character->fall;
			player_collider->Enabled = false;
		}
		LOG("FALL");
		break;
	case ST_RECOVER:
		if (current_animation != &character->recover) {
			character->recover.ResetCurrentFrame();
			current_animation = &character->recover;
		}
		LOG("RECOVER");
		break;
	case ST_CROUCH:
		if (current_animation != &character->crouch) {
			current_animation = &character->crouch;
		}
		LOG("CROUCH");
		break;
	case ST_CROUCH_PUNCH:
		if (current_animation != &character->crouch_punch)
		{
			HitCollider->Enabled = true;
			character->crouch_punch.ResetCurrentFrame();
			current_animation = &character->crouch_punch;
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
		}
		LOG("CROUCH PUNCH");
		break;
	case ST_CROUCH_KICK:
		if (current_animation != &character->crouch_kick) {
			HitCollider->Enabled = true;
			character->crouch_kick.ResetCurrentFrame();
			current_animation = &character->crouch_kick;
			App->audio->Play_chunk(character->jumpattackfx);
			App->audio->Play_chunk(character->punch2fx);
		}
		LOG("CROUCH KICK");
		break;
	case ST_CROUCH_DAMAGE:
		if (current_animation != &character->pose_idle_receive_standing_punch_kick_plus_jump_punch) {
			character->pose_idle_receive_standing_punch_kick_plus_jump_punch.ResetCurrentFrame();
			current_animation = &character->pose_idle_receive_standing_punch_kick_plus_jump_punch;
			if (App->player2->current_state == ST_STANDING_KICK || App->player2->current_state == ST_CROUCH_KICK || App->player2->current_state == ST_STRONG_KICK || App->player2->current_state == ST_NEUTRAL_JUMP_KICK || App->player2->current_state == ST_FORWARD_JUMP_KICK || App->player2->current_state == ST_BACKWARD_JUMP_KICK)
			{
				App->audio->Play_chunk(character->kickfx);
				App->audio->Play_chunk(character->kickfx);
			}
			if (App->player2->current_state == ST_STANDING_PUNCH || App->player2->current_state == ST_STRONG_PUNCH || App->player2->current_state == ST_CROUCH_PUNCH || App->player2->current_state == ST_NEUTRAL_JUMP_PUNCH || App->player2->current_state == ST_FORWARD_JUMP_PUNCH || App->player2->current_state == ST_BACKWARD_JUMP_PUNCH)
			{
				App->audio->Play_chunk(character->dmg);
				App->audio->Play_chunk(character->dmg);
			}
		}
		break;
	case ST_STANDING_BLOCK:
		if (current_animation != &character->standing_block) {
			character->standing_block.ResetCurrentFrame();
			current_animation = &character->standing_block;
		}
		break;	
	case ST_STANDING_BLOCKED:
		if (current_animation != &character->exitBlock) {
			character->exitBlock.ResetCurrentFrame();
			character->exitBlock.ResetDisplacement();
			current_animation = &character->exitBlock;
			App->render->StartSpriteShake(10, 1, character->exitBlock.frames[0].offset);
			App->audio->Play_chunk(character->blockfx);
		}
		break;
	case ST_CROUCH_BLOCK:
		if (current_animation != &character->crouch_block) {
			character->crouch_block.ResetCurrentFrame();
			current_animation = &character->crouch_block;
			current_animation = &character->crouch_block;
		}
		break;
	case ST_IDLE_TO_DAMAGE:
		if (current_animation != &character->pose_idle_receive_standing_punch_kick_plus_jump_punch) {
			character->pose_idle_receive_standing_punch_kick_plus_jump_punch.ResetCurrentFrame();
			current_animation = &character->pose_idle_receive_standing_punch_kick_plus_jump_punch;
			//App->audio->Play_chunk(character->dmg);
			if (App->player2->current_state == ST_STANDING_KICK || App->player2->current_state == ST_CROUCH_KICK || App->player2->current_state == ST_STRONG_KICK || App->player2->current_state == ST_NEUTRAL_JUMP_KICK || App->player2->current_state == ST_FORWARD_JUMP_KICK || App->player2->current_state == ST_BACKWARD_JUMP_KICK)
			{
				App->audio->Play_chunk(character->kickfx);
				App->audio->Play_chunk(character->kickfx);
			}
			if (App->player2->current_state == ST_STANDING_PUNCH || App->player2->current_state == ST_STRONG_PUNCH || App->player2->current_state == ST_CROUCH_PUNCH || App->player2->current_state == ST_NEUTRAL_JUMP_PUNCH || App->player2->current_state == ST_FORWARD_JUMP_PUNCH || App->player2->current_state == ST_BACKWARD_JUMP_PUNCH)
			{
				App->audio->Play_chunk(character->dmg);
				App->audio->Play_chunk(character->dmg);
			}
			if (App->player2->koukenenabled == true)
			{
				App->audio->Play_chunk(character->koukenimpactfx);
				App->player2->koukenenabled = false;
			}
			//App->particles->DeleteLastParticle(currentParticle);

			App->input->StartHaptic(App->input->haptic);

		}
		break;
	case ST_IDLE_TO_DAMAGE_LONG:
		if (current_animation != &character->pose_idle_receive_standing_punch_kick_plus_jump_punch_long) {
			character->pose_idle_receive_standing_punch_kick_plus_jump_punch_long.ResetCurrentFrame();
			current_animation = &character->pose_idle_receive_standing_punch_kick_plus_jump_punch_long;
			App->particles->AddParticle(App->particles->starhit, pivot_player.x + 6, pivot_player.y, COLLIDER_NONE, 200, 0, 1, RYO);
			App->particles->AddParticle(App->particles->starhit, pivot_player.x + 4, pivot_player.y - 10, COLLIDER_NONE, 350, 0, 1, RYO);
			App->particles->AddParticle(App->particles->starhit, pivot_player.x + 10, pivot_player.y + 40, COLLIDER_NONE, 600, 0, 1, RYO);
			App->particles->AddParticle(App->particles->starhit, pivot_player.x , pivot_player.y - 40, COLLIDER_NONE, 800, 0, 1, RYO);
			//App->audio->Play_chunk(character->dmg);
			if (App->player2->current_state == ST_STANDING_KICK || App->player2->current_state == ST_CROUCH_KICK || App->player2->current_state == ST_STRONG_KICK || App->player2->current_state == ST_NEUTRAL_JUMP_KICK || App->player2->current_state == ST_FORWARD_JUMP_KICK || App->player2->current_state == ST_BACKWARD_JUMP_KICK)
			{
				App->audio->Play_chunk(character->kickfx);
				App->audio->Play_chunk(character->kickfx);
			}
			if (App->player2->current_state == ST_STANDING_PUNCH || App->player2->current_state == ST_STRONG_PUNCH || App->player2->current_state == ST_CROUCH_PUNCH || App->player2->current_state == ST_NEUTRAL_JUMP_PUNCH || App->player2->current_state == ST_FORWARD_JUMP_PUNCH || App->player2->current_state == ST_BACKWARD_JUMP_PUNCH)
			{
				App->audio->Play_chunk(character->dmg);
				App->audio->Play_chunk(character->dmg);
			}
			if (App->player2->koukenenabled == true)
			{
				App->audio->Play_chunk(character->koukenimpactfx);
				App->player2->koukenenabled = false;
			}
			if (App->player2->current_state = ST_ULTRA_KICK)
			{
				App->audio->Play_chunk(character->ultrakickhitfx);
				App->audio->Play_chunk(character->ultrakickhitfx);
			}
			//App->particles->DeleteLastParticle(currentParticle);

			App->input->StartHaptic(App->input->haptic);

		}
		break;
	case ST_DAMAGE_IN_AIR:
		if (current_animation != &character->air_damage) {
			character->air_damage.ResetCurrentFrame();
			current_animation = &character->air_damage;
		}
		break;
	case ST_BOUNCE:
		if (current_animation != &character->air_damage_bounce) {
			character->air_damage_bounce.ResetCurrentFrame();
			current_animation = &character->air_damage_bounce;
		}
		break;	

	case ST_FALL_FROM_AIR:
		if (current_animation != &character->air_damage_fall) {
			character->air_damage_fall.ResetCurrentFrame();
			current_animation = &character->air_damage_fall;
		}
		break;
	case ST_RECOVER_FROM_AIR:
		if (current_animation != &character->fall_recover) {
			character->fall_recover.ResetCurrentFrame();
			current_animation = &character->fall_recover;
			pivot_player.y = 150;
		}
		break;
	case ST_TAUNT:
		if (current_animation != &character->taunt) {
			spiritTaunt = true;
			character->taunt.ResetCurrentFrame();
			current_animation = &character->taunt;
			App->audio->Play_chunk(character->tauntfx);
		}
		break;
	case ST_WIN:
		if (current_animation!=&character->win) {
			character->win.ResetCurrentFrame();
			current_animation = &character->win;
			App->audio->Play_chunk(character->winfx);
		}
		break;
	case ST_DEFEAT:
		if (current_animation != &character->defeat) {
			character->defeat.ResetCurrentFrame();
			current_animation = &character->defeat;
			App->input->keyboard_state[SDL_SCANCODE_T] = KEY_UP;
			App->audio->Play_chunk(character->defeatfx);
		}break;
	case ST_RECHARGE:
		if (current_animation != &character->recharge) {
			character->recharge.ResetCurrentFrame();
			current_animation = &character->recharge;
			App->audio->Play_chunk(character->rechargefx);
			rechargeParticle = App->particles->AddParticle(App->particles->recharge, pivot_player.x, pivot_player.y, COLLIDER_NONE, 0, 0, Side, JOHN);
			particleDeleted = false;
		}
		if (Player_Spirit_Value_p1 != 126) {
			Player_Spirit_Value_p1++;
			App->sceneUI->x_spirit_1--;
		}
		LOG("RECHARGE");
		break;
	case ST_ULTRA_KICK:
		if (current_animation != &character->ultrakick)
		{
			spiritUltraKick = true;
			HitCollider->Enabled = true;
			character->ultrakick.ResetCurrentFrame();
			current_animation = &character->ultrakick;
			App->audio->Play_chunk(character->ultrakickfx);
			App->audio->Play_chunk(character->punch2fx);
		}
		break;
	}
	current_state = state;

}


iPoint ModulePlayer_1::GetPosition()
{
	return pivot_player;
}

void ModulePlayer_1::Deal_Damage(ModulePlayer_2& Enemy, int AttackDamage)
{
	if (Enemy.current_state == ST_ULTRA_KICK) {
		last_input = IN_RECEIVE_DAMAGE_LONG;
	}
	else {
		last_input = IN_RECEIVE_DAMAGE;
	}
	HurtColliders[0]->Enabled = false;
	HurtColliders[1]->Enabled = false;
	HurtColliders[2]->Enabled = false;
	LOG("COLLIDERS DIsABLE");

	if (Enemy.Player_Health_Value_p2 - AttackDamage <= 0)
	{
		LOG("\n Someone died");
		Enemy.Player_Health_Value_p2 = 0;
		p2_win++;
		win_check = true;
		last_input = IN_DEFEAT;
		App->slowdown->StartSlowdown(40, 100);
		App->audio->Play_chunk(character->lasthit);
		Module *CurrentScene = nullptr;

		if (App->scene_todo->IsEnabled())
			CurrentScene = App->scene_todo;
	}
	else
	{
		App->slowdown->StartSlowdown(slowdownDuration, 60);
		Enemy.Player_Health_Value_p2 -= AttackDamage;
	}
}

void ModulePlayer_1::CheckHealth(ModulePlayer_2&Enemy)
{

	if ((Enemy.Player_Health_Value_p2 > Player_Health_Value_p1) && App->sceneUI->time_over == true)
	{
		Enemy.Player_Health_Value_p2 = 126;
		Player_Health_Value_p1 = 126;
		App->player2->p1_win++;
	}
}

bool ModulePlayer_1::IsPlayerOnMapLimit() 
{
	if (pivot_player.x + player_collider->rect.w < App->render->CurrentSceneLenght - App->render->CameraLimitR->rect.w
		&& pivot_player.x > App->render->CurrentSceneLenght - App->render->CameraLimitR->rect.w - player_collider->rect.w) 
	{
		return true;
	}
	else
	{
		return false;
	}
}
