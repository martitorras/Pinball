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

	ball_rect.x = 185;
	ball_rect.y = 71;
	ball_rect.w = 15;
	ball_rect.h = 14;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	textures = App->textures->Load("pinball/pinball_elements_2.png");

	left_flipper = App->physics->CreateLeftFlipper();
	right_flipper = App->physics->CreateRightFlipper();
	launcher = App->physics->CreateRectangle(397, 620, 19, 10, b2_dynamicBody);
	launcher_aux = App->physics->CreateCircle(397, 680, 15, b2_staticBody);
	ball = App->physics->CreateCircle(ball_starting_pos.x, ball_starting_pos.y, 8, b2_dynamicBody, false);
	App->physics->CreateLineJoint(launcher, launcher_aux, 30.0f, 1.0f);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(textures);
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
	b2Vec2 anchor_left = left_flipper->joint->GetAnchorB();
	App->renderer->Blit(textures, 140, 645, &left_flipper_rect, 1.0f, left_flipper->GetRotation(), anchor_left.x, anchor_left.y); // Pos of the anchor?
	App->renderer->Blit(textures, 220, 647, &right_flipper_rect, 1.0f, right_flipper->GetRotation(), anchor_left.x, anchor_left.y); // Pos of the anchor?
	
	int x, y;
	ball->GetPosition(x, y);
	App->renderer->Blit(textures, x, y, &ball_rect, 1.0f, ball->GetRotation());

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		launcher->body->ApplyForceToCenter({0, 1000}, true);
	}

	return UPDATE_CONTINUE;
}