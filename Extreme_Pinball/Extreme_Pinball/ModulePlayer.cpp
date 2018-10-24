#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"

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

	launcher_rect.x = 350;
	launcher_rect.y = 289;
	launcher_rect.w = 12;
	launcher_rect.h = 21;
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
	ball->body->SetLinearVelocity(b2Vec2(0, 0));
	ball->body->SetAngularVelocity(0.0f);

	//effects
	hopper = App->audio->LoadFx("pinball/hopper.wav");

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
		launcher->Force(b2Vec2(0.0f, 2000.0f));
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		App->audio->PlayFx(hopper);
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		left_flipper->Turn(-40.0f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		left_flipper->Turn(80.0f);
	}
	else // For the start
	{
		left_flipper->Turn(80.0f);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		right_flipper->Turn(40.0f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		right_flipper->Turn(-80.0f);
	}
	else // For the start
	{
		right_flipper->Turn(-80.0f);
	}

	// Reset ball position
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && App->scene_intro->bls > 0)
	{
		ball->body->SetLinearVelocity(b2Vec2(0, 0));
		ball->body->SetAngularVelocity(0.0f);
		ball->SetPosition(b2Vec2(ball_starting_pos.x, ball_starting_pos.y));
	}

	/* DRAW */

	int x1, y1;
	ball->GetPosition(x1, y1);
	App->renderer->Blit(textures, x1, y1, &ball_rect, 1.0f, ball->GetRotation());

	int x2, y2;
	launcher->GetPosition(x2, y2);
	App->renderer->Blit(textures, x2 + 3, y2 + 2, &launcher_rect, 1.0f, launcher->GetRotation());

	int x3, y3;
	b2Vec2 anchor_flipper_left = left_flipper->joint->GetAnchorB();
	left_flipper->GetPosition(x3, y3);
	App->renderer->Blit(textures, x3 - 22, y3 - 5, &left_flipper_rect, 1.0f, left_flipper->GetRotation(), anchor_flipper_left.x + 20, anchor_flipper_left.y - 10);
	
	int x4, y4;
	b2Vec2 anchor_flipper_right = right_flipper->joint->GetAnchorB();
	right_flipper->GetPosition(x4, y4);
	App->renderer->Blit(textures, x4 - 29, y4 - 7, &right_flipper_rect, 1.0f, right_flipper->GetRotation(), anchor_flipper_right.x + 24, anchor_flipper_right.y - 10);

	App->renderer->Blit(App->scene_intro->background, 381, 647, &App->scene_intro->bottom_launcher_rect);

	return UPDATE_CONTINUE;
}