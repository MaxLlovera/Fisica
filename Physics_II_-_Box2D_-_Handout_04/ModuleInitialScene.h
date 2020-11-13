#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleInitialScene : public Module
{
public:
	ModuleInitialScene(Application* app, bool start_enabled = true);
	~ModuleInitialScene();


	bool Start();

	update_status Update();

	update_status PostUpdate();


	bool CleanUp() override;


private:

	SDL_Texture* introText = nullptr;


};
