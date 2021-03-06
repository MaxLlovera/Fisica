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
	void Teleport();
	void Restart();

public:
	p2List<PhysBody*> bckg;

	
	bool sensed;

	//sensors
	PhysBody* Sensor_Reb1;
	PhysBody* Sensor_Reb2;
	PhysBody* Sensor_Reb3;
	PhysBody* Sensor_rebotblauD;
	PhysBody* Sensor_rebotblauE;
	PhysBody* rebotblauLight;
	PhysBody* Sensor_Audio;

	//Flippers
	SDL_Texture* flipperR_text;
	SDL_Texture* flipperL_text;

	//Textures
	SDL_Texture* Ball_tex;
	SDL_Texture* Trigger_tex;
	SDL_Texture* Life_tex;
	SDL_Texture* light_bouncerR;
	SDL_Texture* light_bouncerL;
	SDL_Texture* light_ball;
	SDL_Texture* background;

	//Audio
	uint bonus_fx = 0;
	uint spoink_fx = 0;
	uint death_fx = 0;
	uint hitflipper_fx = 0;
	uint bump_fx = 0;
	uint pump_fx = 0;
	uint none = 0;
	uint tp_fx = 0;

	//Ray
	p2Point<int> ray;
	bool ray_on;

	//Score
	uint score = 000;
	uint HighScore = 000;

	
	//Fonts
	int whiteFont = -1;
	char scoreText[10] = { "\0" };
	char highScoreText[10] = { "\0" };

	//Lights
	bool iluminarDret = false;
	bool iluminarEsquerra = false;
	bool iluminacioBola1 = false;
	bool iluminacioBola2 = false;
	bool iluminacioBola3 = false;

	int count = 0;
	bool ball_in_game;

	//Dead
	bool dead = false;
	bool deadEnd = false;

	int lifes;

	int countComb;

};
