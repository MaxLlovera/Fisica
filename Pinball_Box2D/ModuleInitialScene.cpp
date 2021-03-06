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
#include "ModuleFonts.h"

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
	introText = App->textures->Load("Assets/Sprites/inicial2.png");

	char lookupTable[] = { "0123456789.,&!'-�abcdefghijklmnopqrstuvwxyz.    " };
	whiteFont = App->fonts->Load("Assets/Sprites/whiteFont.png", lookupTable, 3);
	// Load music
	App->audio->PlayMusic("Assets/Audio/intro_music.ogg");
	App->scene_intro->deadEnd = false;
	bool ret = true;
	return ret;
}

update_status ModuleInitialScene::Update()
{
	App->renderer->Blit(introText, 0, 0);
	
	App->fonts->BlitText(404, 700, whiteFont, App->scene_intro->scoreText);
	App->fonts->BlitText(404, 750, whiteFont, App->scene_intro->highScoreText);

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->fade_to_black->FadeToBlack(this, App->scene_intro, 0);
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