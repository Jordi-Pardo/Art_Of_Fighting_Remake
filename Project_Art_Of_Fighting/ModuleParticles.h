#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"


#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	int born = 0;
	int life = 0;
	bool fx_played = false;
	int Side;
	int lastSide;
	Characters characterType;




	Particle();
	~Particle();
	Particle(const Particle& p);

	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	void DeleteLastParticle(Particle *);
	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	Particle * AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0, int Damage = 0, int Side = 1, Characters type = JOHN);

private:

	Particle* active[MAX_ACTIVE_PARTICLES];
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* currentGraphics = nullptr;
	uint last_particle = 0;

public:
	Characters characterType;

	Particle pre_koouKen;
	Particle koouKen;
	Particle post_koouKen;	
	
	Particle recharge;

	Particle megaSmash;
	Particle post_megaSmash;

	Particle starhit;
	Particle blue_starhit;
	Particle impactfloor;
	Particle vomit;
	Particle blood;
};

#endif // __MODULEPARTICLES_H__