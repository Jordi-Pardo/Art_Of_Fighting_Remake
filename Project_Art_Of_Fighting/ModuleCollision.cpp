#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_COLLISION] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_COLLISION] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_HIT] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_HIT] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_HURT] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_HURT] = false;

	matrix[COLLIDER_PLAYER_COLLISION][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_COLLISION][COLLIDER_PLAYER_COLLISION] = false;
	matrix[COLLIDER_PLAYER_COLLISION][COLLIDER_ENEMY_COLLISION] = true;
	matrix[COLLIDER_PLAYER_COLLISION][COLLIDER_PLAYER_HIT] = false;
	matrix[COLLIDER_PLAYER_COLLISION][COLLIDER_ENEMY_HIT] = false;
	matrix[COLLIDER_PLAYER_COLLISION][COLLIDER_PLAYER_HURT] = false;
	matrix[COLLIDER_PLAYER_COLLISION][COLLIDER_ENEMY_HURT] = false;

	matrix[COLLIDER_ENEMY_COLLISION][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_COLLISION][COLLIDER_PLAYER_COLLISION] = true;
	matrix[COLLIDER_ENEMY_COLLISION][COLLIDER_ENEMY_COLLISION] = false;
	matrix[COLLIDER_ENEMY_COLLISION][COLLIDER_PLAYER_HIT] = false;
	matrix[COLLIDER_ENEMY_COLLISION][COLLIDER_ENEMY_HIT] = false;
	matrix[COLLIDER_ENEMY_COLLISION][COLLIDER_ENEMY_HURT] = false;
	matrix[COLLIDER_ENEMY_COLLISION][COLLIDER_PLAYER_HURT] = false;

	matrix[COLLIDER_PLAYER_HIT][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_HIT][COLLIDER_PLAYER_COLLISION] = false;
	matrix[COLLIDER_PLAYER_HIT][COLLIDER_ENEMY_COLLISION] = false;
	matrix[COLLIDER_PLAYER_HIT][COLLIDER_PLAYER_HIT] = false;
	matrix[COLLIDER_PLAYER_HIT][COLLIDER_ENEMY_HIT] = true;	
	matrix[COLLIDER_PLAYER_HIT][COLLIDER_PLAYER_HURT] = false;	
	matrix[COLLIDER_PLAYER_HIT][COLLIDER_ENEMY_HURT] = true;	
	
	matrix[COLLIDER_ENEMY_HIT][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_HIT][COLLIDER_PLAYER_COLLISION] = false;
	matrix[COLLIDER_ENEMY_HIT][COLLIDER_ENEMY_COLLISION] = false;
	matrix[COLLIDER_ENEMY_HIT][COLLIDER_PLAYER_HIT] = true;
	matrix[COLLIDER_ENEMY_HIT][COLLIDER_ENEMY_HIT] = false;
	matrix[COLLIDER_ENEMY_HIT][COLLIDER_ENEMY_HURT] = false;
	matrix[COLLIDER_ENEMY_HIT][COLLIDER_PLAYER_HURT] = true;

	matrix[COLLIDER_PLAYER_HURT][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_HURT][COLLIDER_PLAYER_COLLISION] = false;
	matrix[COLLIDER_PLAYER_HURT][COLLIDER_ENEMY_COLLISION] = false;
	matrix[COLLIDER_PLAYER_HURT][COLLIDER_PLAYER_HIT] = false;
	matrix[COLLIDER_PLAYER_HURT][COLLIDER_ENEMY_HIT] = true;
	matrix[COLLIDER_PLAYER_HURT][COLLIDER_PLAYER_HURT] = false;
	matrix[COLLIDER_PLAYER_HURT][COLLIDER_ENEMY_HURT] = false;	

	matrix[COLLIDER_ENEMY_HURT][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_HURT][COLLIDER_PLAYER_COLLISION] = false;
	matrix[COLLIDER_ENEMY_HURT][COLLIDER_ENEMY_COLLISION] = false;
	matrix[COLLIDER_ENEMY_HURT][COLLIDER_PLAYER_HIT] = true;
	matrix[COLLIDER_ENEMY_HURT][COLLIDER_ENEMY_HIT] = false;
	matrix[COLLIDER_ENEMY_HURT][COLLIDER_PLAYER_HURT] = false;
	matrix[COLLIDER_ENEMY_HURT][COLLIDER_ENEMY_HURT] = false;

	debug = false;


}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		if (colliders[i]->Enabled == true) 
		{
			c1 = colliders[i];

			// avoid checking collisions already checked
			for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
			{
				// skip empty colliders
				if (colliders[k] == nullptr)
					continue;
					c2 = colliders[k];

					if (c1->CheckCollision(c2->rect) == true)
					{
						if (matrix[c1->type][c2->type] && c1->callback)
							c1->callback->OnCollision(c1, c2);

						if (matrix[c2->type][c1->type] && c2->callback)
							c2->callback->OnCollision(c2, c1);
					}
			}
		}

	
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{

	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if(App->input->keyboard_state[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	if(debug == false)
		return;

	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		if (colliders[i]->Enabled == true) 
		{
			switch (colliders[i]->type)
			{
			case COLLIDER_NONE: // white
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case COLLIDER_WALL: // cian
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
				break;
			case COLLIDER_PLAYER_HURT: // blue
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
				break;
			case COLLIDER_ENEMY_HURT: // blue
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
				break;
			case COLLIDER_PLAYER_COLLISION: // green
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case COLLIDER_ENEMY_COLLISION: // green
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case COLLIDER_PLAYER_HIT: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case COLLIDER_ENEMY_HIT: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			}
		}

		
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(RectSprites rect, COLLIDER_TYPE type, Module* callback, int Damage)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback, Damage);
			break;
		}
	}

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	bool detectedX = true;
	bool detectedY = true;
	// TODO 0: Return true if there is an overlap
	// between argument "r" and property "rect"

	if ((rect.x + rect.w) < r.x || (r.x +r.w) < rect.x) {
		detectedX = false;
	}

	if ((rect.y + rect.h) < r.y || (r.y + r.h) < rect.y)
	{
		detectedY = false;
	}
	
	return detectedX && detectedY;



}