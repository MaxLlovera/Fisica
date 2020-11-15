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
#include "ModuleFonts.h"
#include "ModuleFadeToBlack.h"
#include <stdio.h>
#include <time.h>

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//circle = box = rick = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	//LOAD TEXTURES
	background = App->textures->Load("Assets/Sprites/background.png");
	flipperL_text = App->textures->Load("Assets/Sprites/FlipperL.png");
	flipperR_text = App->textures->Load("Assets/Sprites/FlipperR.png");
	Ball_tex = App->textures->Load("Assets/Sprites/ball.png");
	Trigger_tex = App->textures->Load("Assets/Sprites/spoink.png");
	Life_tex = App->textures->Load("Assets/Sprites/Lifes.png");
	light_bouncerL = App->textures->Load("Assets/Sprites/lightBouncerL.png");
	light_bouncerR = App->textures->Load("Assets/Sprites/lightBouncerR.png");
	light_ball = App->textures->Load("Assets/Sprites/light_ball.png");

	//LOAD AUDIOS/FX
	if (this->IsEnabled() == true)
	{
		App->audio->PlayMusic("Assets/Audio/game_music.ogg");
	}
	hitflipper_fx = App->audio->LoadFx("Assets/Audio/fliphit.wav");
	spoink_fx = App->audio->LoadFx("Assets/Audio/spoink.wav");
	death_fx = App->audio->LoadFx("Assets/Audio/death.wav");
	bump_fx = App->audio->LoadFx("Assets/Audio/bumphit.wav");
	pump_fx = App->audio->LoadFx("Assets/Audio/pumphit.wav");
	tp_fx = App->audio->LoadFx("Assets/Audio/teleport.wav");
	none = App->audio->LoadFx("Assets/Audio/none.wav");

	char lookupTable[] = { "0123456789.,&!'-©abcdefghijklmnopqrstuvwxyz.    " };
	whiteFont = App->fonts->Load("Assets/Sprites/whiteFont.png", lookupTable, 3);

	//trigger
	ball_in_game = false;

	int background1[194] = {
		520, 831,
		520, 254,
		515, 232,
		511, 219,
		509, 207,
		507, 198,
		499, 184,
		490, 163,
		478, 142,
		459, 114,
		436, 91,
		380, 56,
		340, 42,
		303, 33,
		252, 32,
		211, 34,
		163, 48,
		134, 59,
		112, 72,
		96, 85,
		79, 98,
		76, 56,
		74, 42,
		60, 28,
		42, 28,
		27, 43,
		28, 300,
		32, 329,
		35, 354,
		40, 378,
		45, 401,
		53, 431,
		62, 460,
		72, 479,
		92, 505,
		76, 514,
		74, 527,
		93, 527,
		97, 532,
		103, 540,
		103, 552,
		99, 559,
		93, 564,
		84, 566,
		71, 566,
		70, 585,
		53, 588,
		39, 596,
		26, 611,
		23, 624,
		22, 740,
		32, 753,
		44, 759,
		54, 766,
		64, 768,
		79, 776,
		97, 788,
		116, 800,
		139, 814,
		152, 823,
		162, 830,
		166, 833,
		168, 846,
		168, 1500,
		308, 1500,
		312, 835,
		413, 767,
		438, 754,
		457, 738,
		457, 621,
		450, 604,
		435, 592,
		418, 587,
		408, 585,
		407, 567,
		384, 565,
		376, 555,
		375, 541,
		382, 532,
		391, 528,
		406, 528,
		402, 515,
		392, 503,
		391, 497,
		411, 472,
		428, 422,
		440, 373,
		449, 313,
		450, 220,
		441, 182,
		430, 156,
		414, 126,
		415, 120,
		453, 167,
		472, 212,
		482, 252,
		483, 831
	};
	int background_partSuperior[34] = {
		350, 116,
		304, 83,
		260, 68,
		228, 67,
		201, 73,
		174, 83,
		140, 103,
		115, 126,
		146, 113,
		177, 101,
		213, 93,
		266, 90,
		278, 94,
		298, 98,
		318, 106,
		334, 111,
		343, 115
	};
	int blauesquerraSup[46] = {
		119, 454,
		134, 439,
		134, 430,
		108, 394,
		97, 359,
		89, 325,
		87, 315,
		86, 290,
		91, 273,
		92, 258,
		88, 253,
		78, 268,
		74, 282,
		72, 290,
		73, 342,
		76, 361,
		80, 376,
		83, 386,
		87, 398,
		92, 408,
		97, 422,
		103, 435,
		114, 450
	};
	int blauFlipperD[26] = {
		323, 783,
		417, 722,
		419, 622,
		417, 617,
		412, 617,
		408, 621,
		408, 689,
		403, 697,
		389, 709,
		312, 760,
		322, 756,
		333, 768,
		322, 782
	};
	int blauFlipperE[26] = {
		63, 618,
		68, 618,
		71, 622,
		71, 687,
		74, 693,
		82, 702,
		164, 758,
		154, 754,
		142, 767,
		153, 777,
		155, 782,
		61, 720,
		59, 622
	};
	int blaunoPlanta[42] = {
		148, 198,
		149, 228,
		140, 245,
		140, 264,
		147, 282,
		156, 300,
		170, 317,
		188, 334,
		196, 347,
		200, 357,
		199, 369,
		181, 388,
		167, 388,
		153, 381,
		140, 366,
		134, 342,
		130, 322,
		129, 247,
		136, 225,
		142, 207,
		144, 201
	};
	int blauplanta[92] = {
		344, 430,
		344, 439,
		361, 454,
		373, 443,
		383, 420,
		391, 401,
		399, 381,
		404, 354,
		406, 341,
		406, 243,
		400, 225,
		390, 202,
		376, 184,
		353, 162,
		342, 154,
		330, 145,
		329, 249,
		327, 254,
		327, 274,
		324, 282,
		316, 290,
		313, 305,
		316, 310,
		318, 320,
		318, 334,
		314, 337,
		314, 354,
		326, 365,
		333, 357,
		340, 342,
		343, 330,
		347, 315,
		347, 296,
		352, 287,
		361, 283,
		379, 282,
		391, 286,
		393, 294,
		393, 316,
		389, 332,
		385, 347,
		380, 365,
		376, 380,
		367, 399,
		358, 410,
		350, 423
	};
	int blausuperior1[10] = {
		264, 129,
		281, 129,
		281, 172,
		265, 172,
		265, 133
	};
	int blausuperior2[16] = {
		197, 147,
		204, 140,
		213, 140,
		215, 145,
		215, 186,
		203, 194,
		198, 189,
		197, 151
	};
	int rebotador1[32] = {
		262, 210,
		278, 210,
		283, 213,
		286, 218,
		290, 221,
		292, 226,
		292, 240,
		289, 246,
		284, 251,
		279, 255,
		262, 255,
		252, 249,
		247, 240,
		246, 225,
		252, 218,
		257, 212
	};
	int rebotador2[30] = {
		186, 240,
		202, 240,
		211, 246,
		216, 251,
		219, 256,
		218, 270,
		213, 277,
		209, 282,
		203, 287,
		187, 287,
		179, 281,
		171, 271,
		171, 256,
		176, 247,
		182, 241
	};
	int rebotador3[34] = {
		244, 295,
		259, 295,
		264, 298,
		268, 301,
		272, 306,
		274, 312,
		274, 324,
		271, 331,
		267, 337,
		260, 341,
		244, 341,
		237, 336,
		230, 331,
		228, 325,
		228, 310,
		232, 303,
		239, 296
	};
	int rebotblauD[18] = {
		332, 706,
		331, 697,
		367, 626,
		374, 631,
		373, 677,
		368, 684,
		357, 693,
		345, 700,
		337, 705
	};
	int rebotblauE[20] = {
		148, 706,
		148, 696,
		114, 629,
		108, 627,
		105, 632,
		105, 678,
		108, 684,
		120, 693,
		132, 701,
		141, 707
	};
	int SensorAudio[88] = {
		179, 320,
	174, 312,
	166, 302,
	158, 296,
	152, 283,
	147, 270,
	147, 255,
	148, 236,
	154, 229,
	166, 220,
	177, 215,
	184, 210,
	196, 199,
	211, 195,
	226, 189,
	251, 183,
	264, 181,
	283, 182,
	296, 188,
	307, 195,
	314, 210,
	322, 223,
	324, 238,
	322, 246,
	322, 256,
	317, 275,
	314, 284,
	307, 295,
	307, 309,
	307, 320,
	305, 334,
	305, 341,
	304, 350,
	299, 356,
	286, 360,
	272, 364,
	249, 374,
	229, 368,
	215, 362,
	206, 353,
	201, 340,
	198, 326,
	200, 316,
	190, 314
	};


	bckg.add(App->physics->CreateChain(0, 40, background1, 194));
	bckg.add(App->physics->CreateChain(0, 40, background_partSuperior, 34));
	bckg.add(App->physics->CreateChain(0, 40, blauesquerraSup, 46));
	bckg.add(App->physics->CreateChain(0, 40, blauFlipperD, 26));
	bckg.add(App->physics->CreateChain(0, 40, blauFlipperE, 26));
	bckg.add(App->physics->CreateChain(0, 40, blaunoPlanta, 42));
	bckg.add(App->physics->CreateChain(0, 40, blauplanta, 92));
	bckg.add(App->physics->CreateChain(0, 40, blausuperior1, 10));
	bckg.add(App->physics->CreateChain(0, 40, blausuperior2, 16));
	bckg.add(App->physics->CreateChain(0, 40, rebotador1, 32));
	bckg.add(App->physics->CreateChain(0, 40, rebotador2, 30));
	bckg.add(App->physics->CreateChain(0, 40, rebotador3, 34));
	bckg.add(App->physics->CreateChain(0, 40, rebotblauD, 18));
	bckg.add(App->physics->CreateChain(0, 40, rebotblauE, 20));

	
	Sensor_Reb1 = App->physics->CreateChainSensor(0, 40, rebotador1,32);
	Sensor_Reb2 = App->physics->CreateChainSensor(0, 40, rebotador2,30);
	Sensor_Reb3 = App->physics->CreateChainSensor(0, 40, rebotador3,34);
	Sensor_rebotblauD = App->physics->CreateChainSensor(0, 40, rebotblauD,18);
	Sensor_rebotblauE = App->physics->CreateChainSensor(0, 40, rebotblauE,20);
	
	Sensor_Audio = App->physics->CreateChainSensor(0, 40, SensorAudio, 88);
	
	rebotblauLight = App->physics->CreateChainSensor(0, 40, rebotblauD, 18);

	
	Sensor_Reb1->listener = this;
	Sensor_Reb2->listener = this;
	Sensor_Reb3->listener = this;
	Sensor_rebotblauD->listener = this;
	Sensor_rebotblauE->listener = this;
	Sensor_Audio->listener = this;

	App->physics->CreateBall();
	lifes = 5;
	score = 0;
	countComb = 0;
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->physics->Ball = nullptr;
	Ball_tex = nullptr;

	App->fonts->UnLoad(whiteFont);

	App->textures->Unload(background);
	App->textures->Unload(flipperL_text);
	App->textures->Unload(flipperR_text);
	App->textures->Unload(Ball_tex);
	App->textures->Unload(Trigger_tex);
	App->textures->Unload(Life_tex);
	App->textures->Unload(light_bouncerL);
	App->textures->Unload(light_bouncerR);
	App->textures->Unload(light_ball);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//Draw background
	App->renderer->Blit(background, 0, 40);
	App->fonts->BlitText(0, 16, whiteFont, "score.");
	

	if (lifes > 0)
	{
		if (lifes == 5)
		{
			App->renderer->Blit(Life_tex, 536, 0);
			App->renderer->Blit(Life_tex, 496, 0);
			App->renderer->Blit(Life_tex, 456, 0);
			App->renderer->Blit(Life_tex, 416, 0);
			App->renderer->Blit(Life_tex, 376, 0);
		}
		else if (lifes == 4)
		{
			App->renderer->Blit(Life_tex, 536, 0);
			App->renderer->Blit(Life_tex, 496, 0);
			App->renderer->Blit(Life_tex, 456, 0);
			App->renderer->Blit(Life_tex, 416, 0);
		}
		else if (lifes == 3)
		{
			App->renderer->Blit(Life_tex, 536, 0);
			App->renderer->Blit(Life_tex, 496, 0);
			App->renderer->Blit(Life_tex, 456, 0);
		}
		else if (lifes == 2)
		{
			App->renderer->Blit(Life_tex, 536, 0);
			App->renderer->Blit(Life_tex, 496, 0);
		}
		else
		{
			App->renderer->Blit(Life_tex, 536, 0);
		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			ray_on = !ray_on;
			ray.x = App->input->GetMouseX();
			ray.y = App->input->GetMouseY();
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			App->physics->flipperJointL->SetMotorSpeed(30.0f);
		}
		else
		{
			App->physics->flipperJointL->SetMotorSpeed(-30.0f);
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			App->physics->flipperJointR->SetMotorSpeed(-30.0f);
		}
		else
		{
			App->physics->flipperJointR->SetMotorSpeed(30.0f);
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		{
			App->audio->PlayFx(hitflipper_fx, 0);
		}


		//if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		//{
		//	boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));

		//}

		//if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		//{
		//	App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10);
		//}


		//Trigger
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP && !ball_in_game)
		{
			int x, y;
			App->physics->Ball->GetPosition(x, y);

			if (y > 690) {
				srand(time(NULL));
				int random = rand() % 100;
				if (random <= 50) {
					App->physics->Ball->body->ApplyLinearImpulse(b2Vec2(0.0f, -2.05f), App->physics->Ball->body->GetLocalCenter(), true);
				}
				else
				{
					App->physics->Ball->body->ApplyLinearImpulse(b2Vec2(0.0f, -2.5f), App->physics->Ball->body->GetLocalCenter(), true);
				}
				App->audio->PlayFx(spoink_fx, 0);
				ball_in_game = true;
			}
			App->physics->Trigger->body->GetWorld()->DestroyBody(App->physics->Trigger->body);
			App->physics->CreateTrigger(499, 855);

		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && !ball_in_game)
		{
			int x, y;
			App->physics->Trigger->GetPosition(x, y);
			if (count == 0)
			{
				App->physics->Trigger->body->GetWorld()->DestroyBody(App->physics->Trigger->body);
				App->physics->CreateTrigger(499, 860);
				count++;
			}
			if (count == 1)
			{
				App->physics->Trigger->body->GetWorld()->DestroyBody(App->physics->Trigger->body);
				App->physics->CreateTrigger(499, 880);

				count = 0;
			}

		}

		//restart with F2
		if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		{		
			Restart();
		}

		// Prepare for raycast ------------------------------------------------------

		iPoint mouse;
		mouse.x = App->input->GetMouseX();
		mouse.y = App->input->GetMouseY();
		int ray_hit = ray.DistanceTo(mouse);

		fVector normal(0.0f, 0.0f);

		// All draw functions ------------------------------------------------------
		//p2List_item<PhysBody*>* c = circles.getFirst();


		//Draw Flipper Left
		if (App->physics->flipperL != NULL)
		{
			int x, y;
			App->physics->flipperL->GetPosition(x, y);
			App->renderer->Blit(flipperL_text, x, y, NULL, 1.0f, App->physics->flipperL->GetRotation());
		}

		//Draw Flipper Right
		if (App->physics->flipperR != NULL)
		{
			int x, y;
			App->physics->flipperR->GetPosition(x, y);
			App->renderer->Blit(flipperR_text, x, y, NULL, 1.0f, App->physics->flipperR->GetRotation());
		}

		//Draw Ball
		if (App->physics->Ball != NULL && Ball_tex != nullptr)
		{
			int x, y;
			App->physics->Ball->GetPosition(x, y);
			App->renderer->Blit(Ball_tex, x - 3, y - 3, NULL, 1.0f, App->physics->Ball->GetRotation());

			if (y - 3 >= SCREEN_HEIGHT) {
				App->audio->PlayFx(death_fx, 0);
				Restart();
				ball_in_game = false;

			}


		}

		//Draw Trigger
		if (App->physics->Trigger != NULL)
		{
			int x, y;
			App->physics->Trigger->GetPosition(x, y);
			App->renderer->Blit(Trigger_tex, x, y, NULL, 1.0f, App->physics->Trigger->GetRotation());
		}

		//while (c != NULL)
		//{
		//	int x, y;
		//	c->data->GetPosition(x, y);
		//	if (c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
		//		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		//	c = c->next;
		//}

		//c = boxes.getFirst();

		//while (c != NULL)
		//{
		//	int x, y;
		//	c->data->GetPosition(x, y);
		//	App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		//	if (ray_on)
		//	{
		//		int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
		//		if (hit >= 0)
		//			ray_hit = hit;
		//	}
		//	c = c->next;
		//}

		//c = bckg.getFirst();

		//while (c != NULL)
		//{
		//	int x, y;
		//	c->data->GetPosition(x, y);
		//	App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		//	c = c->next;
		//}

		// ray -----------------
		if (ray_on == true)
		{
			fVector destination(mouse.x - ray.x, mouse.y - ray.y);
			destination.Normalize();
			destination *= ray_hit;

			App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

			if (normal.x != 0.0f)
				App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
		}

		//teleport
		if (App->physics->Ball != nullptr)
		{
			Teleport();
		}

		//Bounce Light
		if (iluminarDret)
		{
			App->renderer->Blit(light_bouncerR, 328, 666);
			iluminarDret = false;
		}
		if (iluminarEsquerra)
		{
			App->renderer->Blit(light_bouncerL, 104, 670);
			iluminarEsquerra = false;
		}

		//Balls Light
		if (iluminacioBola1)
		{
			App->renderer->Blit(light_ball, 246, 250);
			iluminacioBola1 = false;
		}
		if (iluminacioBola2)
		{
			App->renderer->Blit(light_ball, 171, 280);
			iluminacioBola2 = false;
		}
		if (iluminacioBola3)
		{
			App->renderer->Blit(light_ball, 228, 334);
			iluminacioBola3 = false;
		}
	}
	else 
	{
		if (score >= HighScore)
		{
			HighScore = score;
			sprintf_s(highScoreText, 10, "%d", HighScore);
		}

		Restart();
		App->fade_to_black->FadeToBlack(this, App->lose_screen, 60);

	}

	//score
	sprintf_s(scoreText, 10, "%d", score);
	if (score < 10) {
		App->fonts->BlitText(240, 16, whiteFont, scoreText);
	}
	else if (score >= 10 && score < 100) {
		App->fonts->BlitText(216, 16, whiteFont, scoreText);
	}
	else if (score >= 100 && score < 1000) {
		App->fonts->BlitText(192, 16, whiteFont, scoreText);
	}
	else if (score >= 1000 && score < 10000) {
		App->fonts->BlitText(168, 16, whiteFont, scoreText);
	}
	else if (score >= 10000 && score < 100000) {
		App->fonts->BlitText(144, 16, whiteFont, scoreText);
	}
	if (score > 20000) {
		App->fonts->BlitText(40, 16, whiteFont, scoreText);
		App->fonts->BlitText(360, 16, whiteFont, scoreText);
	}

	return UPDATE_CONTINUE;
}


void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

	if (bodyA == Sensor_Audio)
	{
		App->audio->PlayFx(none, 0);

	}


	if (lifes > 0)
	{
		if (bodyA == Sensor_Reb1)
		{
			iluminacioBola1 = true;
			if (App->audio->playing == false)
				score += 30;


			App->audio->PlayFx(pump_fx, 0);
			App->audio->playing = true;
		}
		if (bodyA == Sensor_Reb2)
		{

			iluminacioBola2 = true;
			if (App->audio->playing == false)
				score += 30;


			App->audio->PlayFx(pump_fx, 0);
			App->audio->playing = true;
		}
		if (bodyA == Sensor_Reb3)
		{
		
			iluminacioBola3 = true;
			if (App->audio->playing == false)
				score += 30;
			

			App->audio->PlayFx(pump_fx, 0);
			App->audio->playing = true;
		}

		if (bodyA == Sensor_rebotblauD)
		{
			iluminarDret = true;
			
			App->physics->Ball->body->ApplyLinearImpulse(b2Vec2(-0.2f, -1.0f), App->physics->Ball->body->GetLocalCenter(), true);
			App->audio->PlayFx(bump_fx, 0);
		}

		if (bodyA == Sensor_rebotblauE)
		{
			iluminarEsquerra = true;
			
			App->physics->Ball->body->ApplyLinearImpulse(b2Vec2(0.5f, -1.0f), App->physics->Ball->body->GetLocalCenter(), true);
			App->audio->PlayFx(bump_fx, 0);
		}

	}

}

void ModuleSceneIntro::Teleport()
{
	int x, y;
	App->physics->Ball->GetPosition(x, y);

	if (x > 347 && x < 394)
	{
		if (y > 326 && y < 343)
		{
			App->physics->Ball->body->GetWorld()->DestroyBody(App->physics->Ball->body);
			App->physics->Ball = nullptr;
			App->audio->PlayFx(tp_fx, 0);
			score += 50;
			App->physics->Ball = App->physics->CreateCircle(49, 100, 10);
			countComb++;
			if (countComb == 3)
			{
				score += 5000;
			}

		}
	}
}

void ModuleSceneIntro::Restart()
{
	if (lifes > 1)
	{
		App->physics->Ball->body->GetWorld()->DestroyBody(App->physics->Ball->body);
		App->physics->Ball = nullptr;
		App->physics->Ball = App->physics->CreateCircle(500, 600, 10);
		ball_in_game = false;
		dead = false;
		lifes--;	
		
	}
	else
	{
		App->physics->Ball = nullptr;
		ball_in_game = false;
		dead = false;
		deadEnd = true;
		lifes--;
	
	}


}
