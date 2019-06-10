#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 50

#include "Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER_HURT,
	COLLIDER_PLAYER_HIT,
	COLLIDER_PLAYER_COLLISION,
	COLLIDER_ENEMY_HURT,
	COLLIDER_ENEMY_HIT,
	COLLIDER_ENEMY_COLLISION,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;
	bool Enabled = true;
	bool LeftRight;
	int ColliderDamage;
	int Side;

	Collider(RectSprites rectangle, COLLIDER_TYPE type, Module* callback = nullptr, int Damage = 0) :
		type(type),
		callback(callback),
		ColliderDamage(Damage)
	{
		rect.x = rectangle.rect.x;
		rect.y = rectangle.rect.y;
		rect.w = rectangle.rect.w;
		rect.h = rectangle.rect.h;
	}

	void SetRect(SDL_Rect collider,int damage, iPoint pos = { 0,0 }, int Side = 1)
	{

		if (Side == 1) 
		{
			rect.x = collider.x + pos.x;
		}
		else
		{
			rect.x = (-collider.x + pos.x) - collider.w;
		}
		rect.y = collider.y + pos.y;
		rect.w = collider.w;
		rect.h = collider.h;
		ColliderDamage = damage;
	}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	void SetSize (int w, int h)
	{
		rect.w = w;
		rect.h = h;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;

	Collider* AddCollider(RectSprites rect, COLLIDER_TYPE type, Module* callback = nullptr, int Damage = 0);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];

public:
	bool debug = true;
};

#endif // __ModuleCollision_H__