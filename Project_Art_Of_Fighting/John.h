#ifndef __JOHN_H__
#define __JOHN_H__

#include "Character.h"
#include "Application.h"
#include "ModuleTextures.h"
#include"ModulePlayer_1.h"

struct SDL_Texture;

class John : public Character
{
public:
	John(int player);
	~John() {};
	bool Start() override;
	bool CleanUp() override;

	//Special Move Settings
	int SpecialLenght = 0;
	Special_Move *PlayerSpecialMoves[50];
	Timed_Inputs Input_Queue[30];
	inputs *FirstInQueue = nullptr;
	inputs *LastInQueue = nullptr;
	int TopPosition = 0;
	int BottomPosition = 0;
	virtual void AddInput(inputs, float) override;
	virtual inputs CheckCombos(ModulePlayer_1* P1 = nullptr, ModulePlayer_2* P2 = nullptr);
	virtual void AddCombo(int NumberOfInputs, inputs EndState, int ComboSide, inputs Inp...)override;
};

#endif // !__RYO_H__
