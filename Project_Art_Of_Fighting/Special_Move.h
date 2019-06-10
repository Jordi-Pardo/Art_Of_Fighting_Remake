#ifndef __SPECIALMOVE_H__
#define __SPECIALMOVE_H__

#include "Character.h"
#include "Application.h"

class Special_Move
{
public:
	Special_Move();
	~Special_Move() {};

public:

	inputs InputsToCompleteMovement[20];
	int MovementLenght;
	inputs Completed_Input;
	int Combo_Side;

};

#endif // !__CHARACTER_H__
