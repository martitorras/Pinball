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
	SDL_Texture* sprites;
	
	SDL_Rect background_rect;
	SDL_Rect bottom_launcher_rect;
	SDL_Rect bouncer_rect;
	SDL_Rect electric_right;
	SDL_Rect electric_left;
	SDL_Rect p25;
	SDL_Rect p50;

	SDL_Texture* score_tex;
	SDL_Texture* high_score_tex;
	SDL_Texture* balls_tex;

	int font_numbers = -1;
	char num_points[10];
	char num_max_points[10];
	char num_balls[10];
	uint pts = 0;
	uint max_pts;
	uint bls = 5;

	//effects
	uint bounce, strange_bounce, electric_effect, mini_bounce, secret, secret2, t1ah;

	//counters
	uint lcount = 0, ucount = 0, rcount = 0, lecount = 0, recount = 0, p25count = 0, p50count = 0;

	bool is_bouncer_left = false;
	bool is_bouncer_up = false;
	bool is_bouncer_right = false;
	bool is_electric_right = false;
	bool is_electric_left = false;
	bool is_p25 = false;
	bool is_p50 = false;

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

	// Mini bouncers
	PhysBody* miniBouncerTop;
	PhysBody* miniBouncerRight_1;
	PhysBody* miniBouncerRight_2;
	PhysBody* miniBouncerLeft;

	// Little bouncers
	PhysBody* littleBouncerLeft;
	PhysBody* littleBouncerRight;

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

	PhysBody* deathZone;
};
