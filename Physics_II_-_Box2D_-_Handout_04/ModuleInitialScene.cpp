#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleInitialScene.h"
#include "ModuleFadeToBlack.h"

ModuleInitialScene::ModuleInitialScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleInitialScene::~ModuleInitialScene()
{

}


bool ModuleInitialScene::Start()
{
	LOG("Loading background assets");

	// L03: DONE: Load map
	introText = App->textures->Load("Assets/Sprites/inicial.png");
	// Load music
	App->audio->PlayMusic("Assets/Audio/intro_music.ogg");
	
	bool ret = true;
	return ret;
}

update_status ModuleInitialScene::Update()
{
	App->renderer->Blit(introText, 0, 0);
	
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->fade_to_black->FadeToBlack(this, App->scene_intro, 60);
	}
	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleInitialScene::PostUpdate()
{
	bool ret = true;
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) ret = false;

	return UPDATE_CONTINUE;
}

bool ModuleInitialScene::CleanUp()
{
	App->textures->Unload(introText);
	this->Disable();
	return true;
}