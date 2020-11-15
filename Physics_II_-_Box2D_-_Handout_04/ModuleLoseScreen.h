#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleLoseScreen : public Module
{
public:
	ModuleLoseScreen(Application* app, bool start_enabled = false);
	~ModuleLoseScreen();


	bool Start();

	update_status Update();

	update_status PostUpdate();


	bool CleanUp() override;

	//char scoreText[10] = { "\0" };
private:
	int whiteFont = -1;
	
	SDL_Texture* loseText = nullptr;
};

