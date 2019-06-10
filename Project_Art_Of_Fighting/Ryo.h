#ifndef __RYO_H__
#define __RYO_H__

#include "Character.h"
#include"ModulePlayer_1.h"

struct SDL_Texture;

class Ryo : public Character
{
public:
	Ryo(int player);
	~Ryo();
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
	virtual void AddInput(inputs, float);
	virtual inputs CheckCombos(ModulePlayer_1* P1 = nullptr, ModulePlayer_2* P2 = nullptr);
	virtual void AddCombo(int NumberOfInputs, inputs EndState, int ComboSide,inputs Inp...)override;
};

#endif // !__RYO_H__
