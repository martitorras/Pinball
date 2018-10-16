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
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	flipper_texture = App->textures->Load("pinball/pinball_elements_2.png");
	left_flipper = App->physics->CreateLeftFlipper();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	
	// Destroy left flipper
	App->physics->world->DestroyBody(left_flipper->b_attached);
	App->physics->world->DestroyBody(left_flipper->body);
	left_flipper = nullptr;

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	b2Vec2 anchor_left = left_flipper->joint->GetAnchorB();
	App->renderer->Blit(flipper_texture, 140, 645, &left_flipper_rect, 1.0f, left_flipper->GetRotation(), anchor_left.x, anchor_left.y); // Pos of the anchor?

	return UPDATE_CONTINUE;
}