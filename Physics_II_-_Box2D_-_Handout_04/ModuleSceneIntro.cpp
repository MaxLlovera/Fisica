#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
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


	//Backgound
	background = App->textures->Load("Assets/Sprites/background.png");


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
		86, 505,
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
		168, 852,
		308, 853,
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

	
	//sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	
	//Draw background
	App->renderer->Blit(background, 0, 40);
	
	
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
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


	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
	{
		App->physics->CreateCircle(200, 500, 10);
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = bckg.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
