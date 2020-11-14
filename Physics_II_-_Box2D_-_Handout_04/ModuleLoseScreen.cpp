#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleInitialScene.h"
#include "ModuleLoseScreen.h"
#include "ModuleFadeToBlack.h"

ModuleLoseScreen::ModuleLoseScreen(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleLoseScreen::~ModuleLoseScreen()
{

}


bool ModuleLoseScreen::Start()
{
	LOG("Loading background assets");

	// L03: DONE: Load map
	loseText = App->textures->Load("Assets/Sprites/SceneLose.png");
	// Load music
	App->audio->PlayMusic("Assets/Audio/intro_music.ogg");
	
	bool ret = true;
	return ret;
}

update_status ModuleLoseScreen::Update()
{
	App->renderer->Blit(loseText, 0, 0);

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->fade_to_black->FadeToBlack(this, App->initial_scene, 0);
	}
	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleLoseScreen::PostUpdate()
{
	bool ret = true;
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) ret = false;

	return UPDATE_CONTINUE;
}

bool ModuleLoseScreen::CleanUp()
{
	App->textures->Unload(loseText);
	this->Disable();
	return true;
}