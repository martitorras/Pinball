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
	/*circle = box = rick = NULL;*/
	background = NULL;
	background_rect.x = 14;
	background_rect.y = 8;
	background_rect.w = 452;
	background_rect.h = 739;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	/*circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	sensor = App->physics->CreateRectangleSensor(100, 100, 100, 100);*/

	background = App->textures->Load("pinball/pinball.png");

	SetElements();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	/*App->textures->Unload(circle);
	App->textures->Unload(box);
	App->textures->Unload(rick);*/

	App->textures->Unload(background);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	/*if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	}*/

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------
	/*p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}*/

	App->renderer->Blit(background, 0, 0, &background_rect);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
}


void ModuleSceneIntro::SetElements()
{
	int game_boundaries[8] = {
		30, 19,
		450, 18,
		450, 727,
		31, 727
	};

	int ceiling_boundaries[20] = {
		419, 172,
		401, 118,
		369, 80,
		317, 41,
		251, 30,
		194, 39,
		144, 72,
		116, 104,
		125, 142,
		39, 175
	};

	int left_side[24] = {
		38, 133,
		41, 190,
		48, 242,
		58, 285,
		75, 338,
		96, 383,
		122, 423,
		66, 530,
		68, 648,
		163, 698,
		163, 712,
		109, 764
	};

	int right_side[26] = {
		398, 210,
		393, 232,
		369, 246,
		369, 275,
		392, 293,
		394, 395,
		356, 416,
		356, 486,
		375, 501,
		374, 649,
		277, 698,
		277, 711,
		357, 748
	};

	int left_bouncer[6] = {
		20, 244,
		58, 320,
		21, 302
	};

	int right_bouncer[6] = {
		148, 245,
		111, 319,
		149, 300
	};

	int left_supporter[] = {
		85, 552,
		85, 624,
		145, 660,
		156, 660,
		93, 622,
		94, 552
	};

	int right_supporter[12] = {
		288, 659,
		300, 660,
		360, 625,
		361, 551,
		352, 551,
		352, 621
	};

	int ladder[8] = {
		165, 97,
		183, 132,
		196, 126,
		180, 91
	};

	int left_grind[10] = {
		292, 78,
		309, 90,
		323, 106,
		343, 132,
		350, 160
	};

	int right_grind[14] = {
		306, 61,
		332, 76,
		354, 92,
		371, 108,
		383, 125,
		394, 149,
		397, 177
	};


	/* Game boundaries */
	gameBoundaries = App->physics->CreateChain(-14, -10, game_boundaries, 8, b2_staticBody);
	gameBoundaries->listener = this;
	 
	ceiling = App->physics->CreateChain(-15, -8, ceiling_boundaries, 20, b2_staticBody, false);
	ceiling->listener = this;

	leftSide = App->physics->CreateChain(-15, -8, left_side, 24, b2_staticBody, false);
	leftSide->listener = this;

	rightSide = App->physics->CreateChain(-15, -8, right_side, 26, b2_staticBody, false);
	rightSide->listener = this;

	/* Bouncers */
	leftBouncer = App->physics->CreateChain(82, 305, left_bouncer, 6, b2_staticBody);
	leftBouncer->body->GetFixtureList()->SetRestitution(2.0f); // Add more bounce
	leftBouncer->listener = this;

	rightBouncer = App->physics->CreateChain(167, 308, right_bouncer, 6, b2_staticBody);
	rightBouncer->body->GetFixtureList()->SetRestitution(2.0f); // Add more bounce
	rightBouncer->listener = this;

	/* Middle bouncers */
	middleBouncerLeft = App->physics->CreateCircle(187, 255, 24, b2_staticBody);
	middleBouncerLeft->body->GetFixtureList()->SetRestitution(3.0f);
	middleBouncerLeft->listener = this;

	middleBouncerUp = App->physics->CreateCircle(243, 190, 24, b2_staticBody);
	middleBouncerUp->body->GetFixtureList()->SetRestitution(3.0f);
	middleBouncerUp->listener = this;

	middleBouncerRight = App->physics->CreateCircle(289, 258, 24, b2_staticBody);
	middleBouncerRight->body->GetFixtureList()->SetRestitution(3.0f);
	middleBouncerRight->listener = this;

	/* Supporters */
	leftSupporter = App->physics->CreateChain(-15, -10, left_supporter, 12, b2_staticBody);
	leftSupporter->listener = this;

	rightSupporter = App->physics->CreateChain(-15, -5, right_supporter, 12, b2_staticBody);
	rightSupporter->listener = this;

	/* Top "ladders" */
	ladder1 = App->physics->CreateChain(-14, -7, ladder, 8, b2_staticBody);
	ladder1->listener = this;

	ladder2 = App->physics->CreateChain(30, -7, ladder, 8, b2_staticBody);
	ladder2->listener = this;

	ladder3 = App->physics->CreateChain(72, -7, ladder, 8, b2_staticBody);
	ladder3->listener = this;

	/* Ball corridor */
	ballCorridorDown = App->physics->CreateRectangle(396, 660, 21, 0, b2_staticBody, false);
	ballCorridorDown->listener = this;

	ballCorridorLeft = App->physics->CreateRectangle(386, 405, 0, 505, b2_staticBody, false);
	ballCorridorLeft->listener = this;

	ballCorridorRight = App->physics->CreateRectangle(406, 410, 0, 500, b2_staticBody, false);
	ballCorridorRight->listener = this;

	/* Grinds */
	leftGrind = App->physics->CreateChain(-15, -8, left_grind, 10, b2_staticBody, false);
	leftGrind->listener = this;

	rightGrind = App->physics->CreateChain(-15, -8, right_grind, 14, b2_staticBody, false);
	rightGrind->listener = this;

	/* Sensors */
	left_sensor_10 = App->physics->CreateCircle(156, 562, 15, b2_staticBody, true);
	left_sensor_10->listener = this;

	right_sensor_10 = App->physics->CreateCircle(260, 562, 15, b2_staticBody, true);
	right_sensor_10->listener = this;

	right_sensor_10 = App->physics->CreateCircle(260, 562, 15, b2_staticBody, true);
	right_sensor_10->listener = this;

	left_sensor_25 = App->physics->CreateCircle(120, 534, 15, b2_staticBody, true);
	left_sensor_25->listener = this;

	right_sensor_25 = App->physics->CreateCircle(294, 534, 15, b2_staticBody, true);
	right_sensor_25->listener = this;

	left_sensor_50 = App->physics->CreateCircle(91, 510, 15, b2_staticBody, true);
	left_sensor_50->listener = this;

	right_sensor_50 = App->physics->CreateCircle(322, 510, 15, b2_staticBody, true);
	right_sensor_50->listener = this;

	x2_sensor = App->physics->CreateCircle(226, 430, 18, b2_staticBody, true);
	x2_sensor->listener = this;

	top_sensor_1 = App->physics->CreateCircle(136, 85, 5, b2_staticBody, true);
	top_sensor_1->listener = this;

	top_sensor_2 = App->physics->CreateCircle(155, 64, 6, b2_staticBody, true);
	top_sensor_2->listener = this;

	top_sensor_3 = App->physics->CreateCircle(181, 54, 8, b2_staticBody, true);
	top_sensor_3->listener = this;

	top_sensor_4 = App->physics->CreateCircle(215, 43, 10, b2_staticBody, true);
	top_sensor_4->listener = this;

	red_sensor_1 = App->physics->CreateCircle(181, 86, 6, b2_staticBody, true);
	red_sensor_1->listener = this;

	red_sensor_2 = App->physics->CreateCircle(198, 121, 6, b2_staticBody, true);
	red_sensor_2->listener = this;

	red_sensor_3 = App->physics->CreateCircle(225, 86, 6, b2_staticBody, true);
	red_sensor_3->listener = this;

	red_sensor_4 = App->physics->CreateCircle(240, 121, 6, b2_staticBody, true);
	red_sensor_4->listener = this;
}