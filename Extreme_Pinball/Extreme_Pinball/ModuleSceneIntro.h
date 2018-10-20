#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	void SetChains();

public:
	/*p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;

	PhysBody* sensor;

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	uint bonus_fx;*/

	SDL_Texture* background;
	SDL_Rect background_rect;


private:
	// Game boundaries
	PhysBody* gameBoundaries;
	
	// Bouncers
	PhysBody* leftBouncer;
	PhysBody* rightBouncer;

	// Supporters
	PhysBody* leftSupporter;
	PhysBody* rightSupporter;

	// Top "ladders"
	PhysBody* ladder1;
	PhysBody* ladder2;
	PhysBody* ladder3;

	// Sensors
	PhysBody* left_sensor_10;
	PhysBody* right_sensor_10;
	PhysBody* left_sensor_25;
	PhysBody* right_sensor_25;
	PhysBody* left_sensor_50;
	PhysBody* right_sensor_50;
};
