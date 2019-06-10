#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 20

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleSceneTodo;
class ModuleSceneJohn;
class ModulePlayer_1;
class ModulePlayer_2;
class ModuleFadeToBlack;
class ModuleWelcomeScreen;
class ModuleAudio;
class ModuleCongratzScreen;
class ModuleParticles;
class ModuleDebug;
class ModuleCollision;
class ModuleUI;
class Module;
class ModuleFonts;
class ModuleScreenSelection;
class ModuleSlowdown;
class ModuleNeoGeo;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneTodo* scene_todo;
	ModuleSceneJohn* scene_john;
	ModulePlayer_1* player1;
	ModulePlayer_2* player2;
	ModuleFadeToBlack* fade;
	ModuleWelcomeScreen* scene_welcome;
	ModuleAudio* audio;
	ModuleCongratzScreen* scene_congratz;
	ModuleParticles* particles;
	ModuleDebug* debug;
	ModuleCollision* collision;
	ModuleUI* sceneUI;
	ModuleFonts* fonts;
	ModuleScreenSelection* character_selection;
	ModuleSlowdown* slowdown;
	ModuleNeoGeo* neogeo;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__