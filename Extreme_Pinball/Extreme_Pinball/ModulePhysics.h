#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"
#include "p2Point.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

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
	void Turn(float torque);
	void Force(b2Vec2 force);
	void SetPosition(b2Vec2 pos, float angle = 0.0f);
	void SetLinearVelocity(b2Vec2 speed);
	void SetAngularVelocity(float speed);
	void SetBounce(float bounce);

public:
	int width, height;
	b2Body* body;
	b2Body* body_attached; // Improvement only used in flippers
	b2Joint* joint; // Improvement only used in flippers
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

	PhysBody* CreateCircle(int x, int y, int radius, b2BodyType type, bool is_sensor = false);
	PhysBody* CreateRectangle(int x, int y, int width, int height, b2BodyType type, bool is_sensor = false);
	PhysBody* CreateChain(int x, int y, int* points, int size, b2BodyType type, bool closed = true);

	PhysBody* CreateLeftFlipper(int x, int y, int width, int height);
	PhysBody* CreateRightFlipper(int x, int y, int width, int height);

	void CreateDistanceJoint(PhysBody* a, PhysBody* b, float frequency, float damp);
	void CreateRevoluteJoint(PhysBody* a, PhysBody* b, iPoint first_pivot, iPoint second_pivot, int angle_limit_min = INT_MIN, int angle_limit_max = INT_MAX);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);
	b2World* world;
	
private:
	bool debug;
	
	b2MouseJoint* mouse_joint;
	b2Body* ground;
};