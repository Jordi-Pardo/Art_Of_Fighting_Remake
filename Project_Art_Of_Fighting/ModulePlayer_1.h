#ifndef __ModulePlayer1_H__
#define __ModulePlayer1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2Qeue.h"
#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCongratzScreen.h"
#include "ModuleSceneJohn.h"
#include "ModuleSceneTodo.h"
#include "ModulePlayer_2.h"
#include "Character.h"
#include "Ryo.h"
#include "ModuleParticles.h"


struct SDL_Texture;
struct Mix_Chunk;



class ModulePlayer_1 : public Module
{
public:
	ModulePlayer_1();
	~ModulePlayer_1();
	int num = 100;
	bool Start();
	update_status Update();
	bool CleanUp() override;
	bool IsPlayerOnMapLimit();

	void OnCollision(Collider*, Collider*);
	player_state ControlStates();
	void states(int speed);

	iPoint GetPosition();

public:
	int punchrandomizer = 0;
	Collider * player_collider = nullptr;

	player_state current_state = ST_UNKNOWN;

	inputs last_input = IN_UNKNOWN;
	inputs last_input_attack = IN_KICK;
	bool koukenenabled;

	bool isDamaged = false;
	float time = 0.0f;

	SDL_Texture* pivotTexture = nullptr;

	float slowdownDuration;

	RectSprites pivotRect;
	iPoint offset;
	iPoint pivot_player;

	Animation* current_animation = nullptr;
	Animation *shadow_animation = nullptr;
	Animation* current_fx_animation = nullptr;

	Character * character = nullptr;

	Particle * currentParticle = nullptr;

	Particle* rechargeParticle = nullptr;
	bool particleDeleted = false;

	SDL_Rect ActiveScene;
	int timer;
	int p2_win = 0;
	bool win_check = false;
	bool isJumping = false;
	bool isClose = false;

	//bool BackColision, FrontColision;
	Collider* CurrentColider = nullptr;
	Collider* HitCollider = nullptr;
	Collider* HurtColliders[3];


	//PlayerStats
	int Player_Health_Value_p1;
	int Player_Spirit_Value_p1;

	void Deal_Damage(ModulePlayer_2& Enemy, int AttackDamage);
	void CheckHealth(ModulePlayer_2&Enemy);

	int Side;
	SDL_Texture* Player_texture;
	SDL_Texture* Player_Health_BG;
	SDL_Texture* Player_Health_BG_Empty;
	SDL_Texture* Player_Health;
	SDL_Texture* Player_SpiritGreen;
	SDL_Texture* Player_SpiritYellow;
	SDL_Texture* Player_SpiritRed;
	int speed;
	bool WallColiding = false;
	bool spiritKouKen = false;
	bool spiritTaunt = false;
	bool spiritUltraKick = false;

	ModulePlayer_2* Enemy;

	int tick1 = 0, tick2 = 0;
};

#endif