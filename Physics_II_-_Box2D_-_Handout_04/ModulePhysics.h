#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"
#include "Application.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

struct Flipper {

	PhysBody* flipper = nullptr;
	PhysBody* axis = nullptr;
	bool mov = false;

	b2RevoluteJoint* Rjoint = nullptr;
};

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius);
	PhysBody* CreateCircleStatic(int x, int y, int radius);
	PhysBody* CreateRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangleStatic(int x, int y, int width, int height);

	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);

	PhysBody* CreateChain(int x, int y, int* points, int size);
	PhysBody* CreateChainSensor(int x, int y, int* points, int size);
	
	void CreateFlippers();
	void CreateBall();
	void CreateTrigger(int x, int y);

	b2RevoluteJoint* CreateJoint(b2JointDef*);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	b2RevoluteJointDef flipperJoint;
	b2RevoluteJoint* flipperJointL;
	b2RevoluteJoint* flipperJointR;
	PhysBody* flipperL = nullptr;
	PhysBody* flipperR = nullptr;
	PhysBody* axisL = nullptr;
	PhysBody* axisR = nullptr;
	PhysBody* Ball = nullptr;
	PhysBody* Trigger = nullptr;
	SDL_Texture* rTextFlip = nullptr;
	SDL_Texture* lTextFlip = nullptr;
	b2World* world;
	b2Body* ground;
	b2Body* body_clicked = nullptr;
private:

	bool debug;
	b2MouseJoint* mouse_joint;

	
	bool b_Clicked;
	bool Joint_Created = false;
};