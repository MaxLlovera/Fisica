#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = false);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	void Restart();

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> bckg;

	
	bool sensed;

	//sensors
	PhysBody* Sensor_Reb1;
	PhysBody* Sensor_Reb2;
	PhysBody* Sensor_Reb3;
	PhysBody* Sensor_rebotblauD;
	PhysBody* Sensor_rebotblauE;
	PhysBody* rebotblauLight;


	SDL_Texture* flipperR_text;
	SDL_Texture* flipperL_text;

	SDL_Texture* flipper_text;
	SDL_Texture* Ball_tex;
	SDL_Texture* Trigger_tex;
	SDL_Texture* Life_tex;

	SDL_Texture* background;
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	uint bonus_fx = 0;
	uint spoink_fx = 0;
	uint death_fx = 0;
	uint hitflipper_fx = 0;
	p2Point<int> ray;
	bool ray_on;

	bool ball_in_game;

	bool dead = false;
	
	int score = 0;
	int lifes;

};
