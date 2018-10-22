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
	void SetElements();

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
	PhysBody* ceiling;
	PhysBody* leftSide;
	PhysBody* rightSide;
	
	// Bouncers
	PhysBody* leftBouncer;
	PhysBody* rightBouncer;

	// Middle Bouncers
	PhysBody* middleBouncerLeft;
	PhysBody* middleBouncerUp;
	PhysBody* middleBouncerRight;

	// Supporters
	PhysBody* leftSupporter;
	PhysBody* rightSupporter;

	// Top "ladders"
	PhysBody* ladder1;
	PhysBody* ladder2;
	PhysBody* ladder3;

	// Ball corridor
	PhysBody* ballCorridorDown;
	PhysBody* ballCorridorLeft;
	PhysBody* ballCorridorRight;

	//grind
	PhysBody* leftGrind;
	PhysBody* rightGrind;

	// Sensors
	PhysBody* left_sensor_10;
	PhysBody* right_sensor_10;
	PhysBody* left_sensor_25;
	PhysBody* right_sensor_25;
	PhysBody* left_sensor_50;
	PhysBody* right_sensor_50;
	PhysBody* x2_sensor;

	PhysBody* top_sensor_1;
	PhysBody* top_sensor_2;
	PhysBody* top_sensor_3;
	PhysBody* top_sensor_4;

	PhysBody* red_sensor_1;
	PhysBody* red_sensor_2;
	PhysBody* red_sensor_3;
	PhysBody* red_sensor_4;

	PhysBody* grind_sensor;
};
