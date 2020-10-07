#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include "Box2D/Box2D/Box2D.h"



// TODO 1: Include Box 2 header and library
#ifdef _DEBUG

#pragma comment ( lib, "Box2D/libx86/Debug/Box2D.lib")

#else

#pragma comment ( lib, "Box2D/libx86/Release/Box2D.lib")

#endif // _DEBUG



ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;

}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	// TODO 2: Create a private variable for the world
	b2Vec2 gravity(0.0f, 10.0f);
	
	myWorld = new b2World(gravity);


	// - You need to send it a default gravity
	// - You need init the world in the constructor
	// - Remember to destroy the world after using it


	// TODO 4: Create a a big static circle as "ground"
	b2BodyDef circle_def;
	circle_def.type = b2_staticBody;
	circle_def.position.Set(PIXEL_TO_METER(SCREEN_WIDTH/2), PIXEL_TO_METER(SCREEN_HEIGHT/2));
	b2Body* circle = myWorld->CreateBody(&circle_def);
	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METER(200);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	circle->CreateFixture(&fixture);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)
	myWorld->Step(1.0f / 60.0f, 8, 3);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		b2BodyDef bola_def;
		bola_def.type = b2_dynamicBody;
		bola_def.position.Set(PIXEL_TO_METER(App->input->GetMouseX()), PIXEL_TO_METER (App->input->GetMouseY()));
		b2Body* bola = myWorld->CreateBody(&bola_def);

		b2CircleShape shape;
		shape.m_radius = PIXEL_TO_METER(50);
		b2FixtureDef fixture;
		fixture.shape = &shape;
		bola->CreateFixture(&fixture);
	}


	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	
	for(b2Body* b = myWorld->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METER_TO_PIXEL(pos.x), METER_TO_PIXEL(pos.y), METER_TO_PIXEL(shape->m_radius), 255, 255, 255);
				}
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete myWorld;

	return true;
}
