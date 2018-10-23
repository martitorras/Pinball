#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	left_flipper_rect.x = 15;
	left_flipper_rect.y = 130;
	left_flipper_rect.w = 56;
	left_flipper_rect.h = 18;

	right_flipper_rect.x = 87;
	right_flipper_rect.y = 131;
	right_flipper_rect.w = 56;
	right_flipper_rect.h = 18;

	ball_rect.x = 184;
	ball_rect.y = 72;
	ball_rect.w = 15;
	ball_rect.h = 14;

	launcher_rect.x = 349;
	launcher_rect.y = 289;
	launcher_rect.w = 13;
	launcher_rect.h = 2;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	textures = App->textures->Load("pinball/pinball_elements_2.png");

	left_flipper = App->physics->CreateLeftFlipper(168, 662, 60, 10);
	right_flipper = App->physics->CreateRightFlipper(244, 662, 60, 10);

	launcher = App->physics->CreateRectangle(397, 620, 19, 10, b2_dynamicBody);
	launcher->body->GetFixtureList()->SetRestitution(0.4f);
	launcher_aux = App->physics->CreateCircle(397, 680, 15, b2_staticBody, true);
	App->physics->CreateDistanceJoint(launcher, launcher_aux, 40.0f, 1.0f);

	ball = App->physics->CreateCircle(ball_starting_pos.x, ball_starting_pos.y, 6, b2_dynamicBody);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(textures);
	 
	// DELETE ALL BODIESSSSSSSSSSSSSSSSSSSSSSSSS

	/* necessary ?-
	// Destroy left flipper
	App->physics->world->DestroyBody(left_flipper->b_attached);
	App->physics->world->DestroyBody(left_flipper->body);
	left_flipper = nullptr;

	App->physics->world->DestroyBody(right_flipper->b_attached);
	App->physics->world->DestroyBody(right_flipper->body);
	right_flipper = nullptr;
	*/
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		launcher->body->ApplyForceToCenter({0, 2000}, true);
	}	

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		left_flipper->body->ApplyTorque(-60.0f, true);
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		left_flipper->body->ApplyTorque(100.0f, true);
	}
	else // For the start
	{
		left_flipper->body->ApplyTorque(100.0f, true);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		right_flipper->body->ApplyTorque(60.0f, true);
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		right_flipper->body->ApplyTorque(-100.0f, true);
	}
	else // For the start
	{
		right_flipper->body->ApplyTorque(-100.0f, true);
	}

	// Reset ball position
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		ball->body->SetTransform(b2Vec2(PIXEL_TO_METERS(ball_starting_pos.x), PIXEL_TO_METERS(ball_starting_pos.y)), 0.0f);
	}

	/* DRAW */

	int x1, y1;
	ball->GetPosition(x1, y1);
	App->renderer->Blit(textures, x1, y1, &ball_rect, 1.0f, ball->GetRotation());

	int x2, y2;
	launcher->GetPosition(x2, y2);
	App->renderer->Blit(textures, x2 + 1, y2, &launcher_rect, 1.0f, launcher->GetRotation());

	int x3, y3;
	b2Vec2 anchor_flipper_left = left_flipper->joint->GetAnchorB();
	left_flipper->GetPosition(x3, y3);
	App->renderer->Blit(textures, x3 - 22, y3 - 11, &left_flipper_rect, 1.0f, left_flipper->GetRotation(), anchor_flipper_left.x + 18, anchor_flipper_left.y - 10);
	
	int x4, y4;
	b2Vec2 anchor_flipper_right = right_flipper->joint->GetAnchorB();
	right_flipper->GetPosition(x4, y4);
	App->renderer->Blit(textures, x4, y4, &right_flipper_rect, 1.0f, right_flipper->GetRotation(), anchor_flipper_right.x + 50, anchor_flipper_right.y - 10);

	return UPDATE_CONTINUE;
}