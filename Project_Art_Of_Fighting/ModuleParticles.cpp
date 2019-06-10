#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "RectSprites.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

void ModuleParticles::DeleteLastParticle(Particle * particle)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; i++)
	{
		if (active[i] == particle) {
			particle = nullptr;
			delete active[i];
			active[i] = nullptr;
		}
	}
}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");

	
	graphics = App->textures->Load("Assets/ryo_sprite_sheet.png");
	graphics2 = App->textures->Load("Assets/john_sprite_sheet.png");

	// Ko'ou Ken particle
	//Charge energy
	pre_koouKen.anim.SetReverseOffset({ 35,-39 }, 2);
	pre_koouKen.anim.PushBack({939,940,19,45},-33,-39,2);
	pre_koouKen.anim.SetReverseOffset({ 50,-37 }, 2);
	pre_koouKen.anim.PushBack({683,869,23,36},-55,-37,2);
	pre_koouKen.anim.SetReverseOffset({ 40,-21 }, 3);
	pre_koouKen.anim.PushBack({707,869,22,36},-49,-21,3);
	pre_koouKen.anim.SetReverseOffset({ 45,-17 }, 1);
	pre_koouKen.anim.PushBack({730,878,26,27},-49,-17,1);
	pre_koouKen.anim.SetReverseOffset({ 45,-15 }, 1);
	pre_koouKen.anim.PushBack({730,878,26,27},-54,-15,1);
	pre_koouKen.anim.loop = false;
	pre_koouKen.anim.speed = 0.32f;

	////Shoot energy
	koouKen.anim.SetReverseOffset({ -3,-20 }, 5);
	koouKen.anim.PushBack({683,912,54,39},-3,-20,5);
	koouKen.anim.SetReverseOffset({ -3,-23 }, 5);
	koouKen.anim.PushBack({737,905,72,47},-21,-23,5);
	koouKen.anim.SetReverseOffset({ -3,-16 }, 5);
	koouKen.anim.PushBack({809,920,53,31},-2,-16,5);
	koouKen.anim.SetReverseOffset({ -3,-11 }, 5);
	koouKen.anim.PushBack({862,930,36,21},15,-11,5);
	koouKen.anim.loop = true;
	koouKen.life = 1500;
	koouKen.speed = { 10,0 };
	koouKen.anim.speed = 1.2f;

	//Megasmash
	megaSmash.anim.SetReverseOffset({-75,0}, 5);
	megaSmash.anim.PushBack({681,139,83,27},0,0,5);
	megaSmash.anim.SetReverseOffset({-75,1}, 5);
	megaSmash.anim.PushBack({682,168,78,25},5,1,5);
	megaSmash.life = 1500;
	megaSmash.speed ={ 10,0 };
	megaSmash.anim.speed = 0.5f;
	
	//Hitted particle
	post_koouKen.anim.SetReverseOffset({ 10,-21 }, 2);
	post_koouKen.anim.PushBack({942,612,30,37},10,-21,2);
	post_koouKen.anim.SetReverseOffset({ 10, -21 }, 2);
	post_koouKen.anim.PushBack({973,612,22,37},15, -21, 2);
	post_koouKen.anim.SetReverseOffset({ 10, -21 }, 2);
	post_koouKen.anim.PushBack({942,664,20,37},15,-21,2);
	post_koouKen.anim.SetReverseOffset({ 13,-20 }, 2);
	post_koouKen.anim.PushBack({962,665,22,36},18,-20,2);
	post_koouKen.anim.SetReverseOffset({ 5,-20 }, 2);
	post_koouKen.anim.PushBack({985,665,39,36},-3,-20,2);
	post_koouKen.anim.SetReverseOffset({ 9,-24 }, 3);
	post_koouKen.anim.PushBack({998,612,25,50},9,-24,3);
	post_koouKen.anim.speed = 1.0f;
	post_koouKen.anim.loop = false;

		//EFFECTS
	//starhit animation
	starhit.anim.SetReverseOffset({0,0}, 2);
	starhit.anim.PushBack({ 975 ,885,18,23 }, 0, 0, 2);
	starhit.anim.SetReverseOffset({-5,-8}, 2);
	starhit.anim.PushBack({ 1008 ,879,29,36 }, -5, -8, 2);
	starhit.anim.speed = 0.5f;
	starhit.anim.loop = false;	
	
	//blue starhit animation
	blue_starhit.anim.SetReverseOffset({0,0}, 2);
	blue_starhit.anim.PushBack({ 877 ,143,12,12 }, 0, 0, 2);
	blue_starhit.anim.SetReverseOffset({-5,-8}, 2);
	blue_starhit.anim.PushBack({ 904 ,138,19,22 }, -5, -8, 2);
	blue_starhit.anim.speed = 0.5f;
	blue_starhit.anim.loop = false;

	//impact floor animation
	impactfloor.anim.PushBack({ 977 ,923,16,12 }, 0, 0, 0);
	impactfloor.anim.PushBack({ 1013 ,922,18,15 }, 0, 0, 0);
	impactfloor.anim.PushBack({ 973 ,951,24 ,21 }, 0, 0, 0);
	impactfloor.anim.PushBack({ 1011 ,948,24,24 }, 0, 0, 0);

	//vomit animation
	vomit.anim.PushBack({ 983 ,1042,11,12 }, 0, 0, 0);
	vomit.anim.PushBack({ 1002 ,1042,18,13 }, 0, 0, 0);
	vomit.anim.PushBack({ 986 ,1068,10,7 }, 0, 0, 0);
	vomit.anim.PushBack({ 1010 ,1067,5,5 }, 0, 0, 0);

	//blood animation
	blood.anim.PushBack({ 962 ,1155,6,6 }, 0, 0, 0);
	blood.anim.PushBack({ 959 ,1175,48,17 }, 0, 0, 0);
	blood.anim.PushBack({ 961 ,1204,43,16 }, 0, 0, 0);
	blood.anim.PushBack({ 960 ,1224,49,16 }, 0, 0, 0);


	//Recharge
	recharge.anim.SetReverseOffset({ 25,-40 }, 5);
	recharge.anim.PushBack({ 825 ,500,44,22 }, -4, -40, 5);
	recharge.anim.SetReverseOffset({ 25,-40 }, 5);
	recharge.anim.PushBack({ 825 ,533,44,25 }, -4, -40, 5);
	recharge.anim.SetReverseOffset({ 25,-40 }, 5);
	recharge.anim.PushBack({ 825 ,568,45,25 }, -5, -40, 5);
	recharge.anim.speed = 0.5f;
	recharge.anim.loop = true;
	recharge.life = 10000;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}


// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];
		
		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			RectSprites r = p->anim.GetCurrentFrame();
			if (p->characterType == RYO) {
				if (p->Side == 2)
				{
					App->render->Blit(graphics, p->position.x + r.offset_reverse.x, p->position.y + r.offset_reverse.y, &r, 1, p->Side);
				}

				else if (p->Side == 1)
				{
					App->render->Blit(graphics, p->position.x + r.offset.x, p->position.y + r.offset.y, &r, 1, p->Side);

				}
			}		
			else if (p->characterType == JOHN) {
				if (p->Side == 2)
				{
					App->render->Blit(graphics2, p->position.x + r.offset_reverse.x, p->position.y + r.offset_reverse.y, &r, 1, p->Side);
				}

				else if (p->Side == 1)
				{
					App->render->Blit(graphics2, p->position.x + r.offset.x, p->position.y + r.offset.y, &r, 1, p->Side);

				}
			}
			if(p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

Particle * ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, int Damage, int Side, Characters type)
{

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->characterType = type;
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->Side = Side;
			last_particle++;
			if (collider_type != COLLIDER_NONE) {
				RectSprites r = p->anim.GetCurrentFrame();
				if (p->Side == 1) {
				r.rect.x = x - 1000;
				r.rect.y = y - 1000;
				}
				else {
				r.rect.x = x + 1000;
				r.rect.y = y + 1000;

				}
				r.rect.y = y;
				p->collider = App->collision->AddCollider(r, collider_type, this, Damage);
				p->collider->Side = p->Side;

			}
			active[i] = p;
			
			return active[i];
		}
	}
}

void ModuleParticles::OnCollision(Collider * c1, Collider * c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{

		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			int offsetX = 0;

			if (c1->Side == 1) {
				offsetX = active[i]->collider->rect.w / 2;
			}
			else if (c1->Side == 2) {
				offsetX = -active[i]->collider->rect.w / 4;
			}
			//AddParticle(post_koouKen, c1->rect.x + offsetX, c1->rect.y  + c1->rect.y/7,COLLIDER_NONE,0,0,c1->Side,RYO);

			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}


// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}
Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life), Side(p.Side)
{}


bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		int ticks = SDL_GetTicks();
		int num = ticks - born;
		if (num > life) {
			ret = false;
		}
	}
	else
		if (anim.Finished()) {
			ret = false;
		}
	if (SDL_GetTicks() >= born)
	{

		if (Side == 1) 
		{
			position.x += speed.x;
			position.y += speed.y;
		}
		else
		{
			position.x -= speed.x;
			position.y -= speed.y;
		}

		if (collider != nullptr) {
			if (Side == 1) {
				collider->SetPos(position.x - collider->rect.w/10 + 8 , position.y - collider->rect.h/10 +2);
			}
			else {
				collider->SetPos(position.x - collider->rect.w/10 -68, position.y - collider->rect.h / 10 + 2);
			}
		}
	}



	return ret;
}