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

	SetChains();

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


void ModuleSceneIntro::SetChains()
{
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

	/* Bouncers */
	leftBouncer = App->physics->CreateChain(82, 308, left_bouncer, 6, b2_staticBody);
	leftBouncer->body->GetFixtureList()->SetRestitution(2.0f); // Add more bounce
	leftBouncer->listener = this;

	rightBouncer = App->physics->CreateChain(167, 308, right_bouncer, 6, b2_staticBody);
	rightBouncer->body->GetFixtureList()->SetRestitution(2.0f); // Add more bounce
	rightBouncer->listener = this;

	/* Sensors */
	left_sensor_10 = App->physics->CreateRectangleSensor(156, 562, 18, 18);
	//left_sensor_10->body->GetFixtureList()->SetSensor(); // not necessary, it can be a fuction parameter on the createrectangle() funciton, for example, and will not be needed to create this function hehexd.
	left_sensor_10->listener = this;

	right_sensor_10 = App->physics->CreateRectangleSensor(260, 562, 18, 18);
	right_sensor_10->listener = this;

	right_sensor_10 = App->physics->CreateRectangleSensor(260, 562, 18, 18);
	right_sensor_10->listener = this;

	left_sensor_25 = App->physics->CreateRectangleSensor(119, 534, 18, 18);
	left_sensor_25->listener = this;

	right_sensor_25 = App->physics->CreateRectangleSensor(293, 534, 18, 18);
	right_sensor_25->listener = this;

	left_sensor_50 = App->physics->CreateRectangleSensor(91, 510, 18, 18);
	left_sensor_50->listener = this;

	right_sensor_50 = App->physics->CreateRectangleSensor(322, 510, 18, 18);
	right_sensor_50->listener = this;
}