#pragma once

#include "p2List.h"
#include "Globals.h"

class Module;
class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModulePlayer;
class ModuleFadeToBlack;
class ModuleInitialScene;
class ModuleSceneIntro;
class ModuleLoseScreen;
class ModulePhysics;
class ModuleFonts;

class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModulePlayer* player;
	ModuleFadeToBlack* fade_to_black;
	ModuleFonts* fonts;
	ModuleInitialScene* initial_scene;
	ModuleSceneIntro* scene_intro;
	ModuleLoseScreen* lose_screen;
	ModulePhysics* physics;

private:

	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
};