#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Character.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "Animation.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "Special_Move.h"

struct SDL_Texture;
struct Mix_Chunk;
class Special_Move;

class Character
{
public:
	Character() {};
	~Character() {};
	virtual bool Start() = 0;
	virtual bool CleanUp() = 0;

public:

	int player;
	Characters characterType;

	bool isBlocking = false;

	int colliderOffsetX;

	virtual void AddInput(inputs, float) = 0;
	virtual inputs CheckCombos(ModulePlayer_1*, ModulePlayer_2*) = 0;
	virtual void AddCombo(int NumberOfInputs, inputs EndState,int ComboSide, inputs Inp...) = 0;

	int specialDmg;
	//Basic moves
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation kick;
	Animation jump;
	Animation fall;
	Animation recover;
	Animation fall_recover;
	Animation jumpkick;
	Animation jumppunch;
	Animation jump_forward;
	Animation jump_backward;
	Animation win;
	Animation defeat;
	Animation taunt;
	Animation thrown;
	Animation recharge;
	Animation ultrakick;
	Animation pose_idle_receive_standing_punch_kick_plus_jump_punch;
	Animation pose_idle_receive_standing_punch_kick_plus_jump_punch_long;
	Animation pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch;
	Animation pose_idle_receive_crouch_kick;
	Animation air_damage;
	Animation air_damage_fall;
	Animation air_damage_bounce;
	Animation shadow;

	Animation pose_crouch_receive_standing_crouch_kick;
	Animation pose_crouch_receive_crouch_punch;

	Animation exitBlock;

	Animation pose_jump_receive_dmg; //Not sure for prototype

	//Crouch Moves
	Animation crouch;
	Animation crouch_punch;
	Animation crouch_kick;

	//Special moves
	Animation koouKen;

	//Blocking moves
	Animation standing_block;
	Animation crouch_block;

	//Strong Atacks
	Animation c_punch;
	Animation c_kick;

	//Textures
	SDL_Texture* graphics = nullptr;

	Mix_Chunk *punch1fx = NULL;
	Mix_Chunk *punch2fx = NULL;
	Mix_Chunk *punchfx = NULL;
	Mix_Chunk *kickfx = NULL;
	Mix_Chunk *kooukenfx = NULL;
	Mix_Chunk *jumpfx = NULL;
	Mix_Chunk *dmg = NULL;
	Mix_Chunk *tauntfx = NULL;
	Mix_Chunk *lasthit = NULL;
	Mix_Chunk *rechargefx = NULL;
	Mix_Chunk *defeatfx = NULL;
	Mix_Chunk *winfx = NULL;
	Mix_Chunk *fallfx = NULL;
	Mix_Chunk *jumpattackfx = NULL;
	Mix_Chunk *koukenimpactfx = NULL;
	Mix_Chunk *ultrakickfx = NULL;
	Mix_Chunk *ultrakickhitfx = NULL;
	Mix_Chunk *kickfx2 = NULL;
	Mix_Chunk *blockfx = NULL;

};

#endif // !__CHARACTER_H__
