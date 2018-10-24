#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	/*circle = box = rick = NULL;*/
	background_rect = { 14, 8, 452, 739 };
	bouncer_rect = { 268, 68, 54, 55 };
	electric_right = { 103, 240, 56, 88 };
	electric_left = { 15, 240, 52, 88 };

	bottom_launcher_rect = { 395, 655, 32, 31};

	p25 = { 22, 22, 36, 34 };
	p50 = { 123, 23, 34, 33 };

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	background = App->textures->Load("pinball/pinball.png");
	sprites = App->textures->Load("pinball/pinball_elements_2.png");
	score_tex = App->textures->Load("pinball/score.png");
	high_score_tex = App->textures->Load("pinball/high_score.png");
	balls_tex = App->textures->Load("pinball/balls.png");

	bounce = App->audio->LoadFx("pinball/bounce_cartoon.wav");
	strange_bounce = App->audio->LoadFx("pinball/computer_bounce.wav");
	electric_effect = App->audio->LoadFx("pinball/electric.wav");
	mini_bounce = App->audio->LoadFx("pinball/mini_bouncer.wav");
	secret = App->audio->LoadFx("pinball/tyler-fkin-1.wav");
	secret2 = App->audio->LoadFx("pinball/gett-of-my-game-tyler1.wav");
	t1ah = App->audio->LoadFx("pinball/ah-tyler1.wav");

	App->audio->PlayMusic("pinball/background_music.ogg", 2);

	font_numbers = App->fonts->Load("pinball/font_numbers.png", "0123456789", 1);

	SetElements();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(background);
	App->textures->Unload(sprites);
	App->textures->Unload(score_tex);
	App->textures->Unload(high_score_tex);
	App->textures->Unload(balls_tex);

	App->fonts->UnLoad(font_numbers);

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
	App->renderer->Blit(score_tex, 20, 32);
	App->renderer->Blit(high_score_tex, 20, 14);
	App->renderer->Blit(balls_tex, 20, 50);

	sprintf_s(num_points, 10, "%7d", pts);
	sprintf_s(num_max_points, 10, "%7d", max_pts);
	sprintf_s(num_balls, 10, "%7d", bls);
	App->fonts->Blit(100, 32, font_numbers, num_points);
	App->fonts->Blit(150, 14, font_numbers, num_max_points);
	App->fonts->Blit(100, 50, font_numbers, num_balls);

	//bouncers
	if (is_bouncer_left)
	{
		App->renderer->Blit(sprites, 158, 228, &bouncer_rect);
		if (lcount < 30) ++lcount;
		else
		{
			lcount = 0;
			is_bouncer_left = false;
		}
	}
	if (is_bouncer_up)
	{
		App->renderer->Blit(sprites, 214, 162, &bouncer_rect);
		if (ucount < 30) ++ucount;
		else
		{
			ucount = 0;
			is_bouncer_up = false;
		}
	}
	if (is_bouncer_right)
	{
		App->renderer->Blit(sprites, 262, 231, &bouncer_rect);
		if (rcount < 30) ++rcount;
		else
		{
			rcount = 0;
			is_bouncer_right = false;
		}
	}

	//electric bouncers
	if (is_electric_right)
	{
		App->renderer->Blit(sprites, 270, 545, &electric_right);
		if (recount < 20) ++recount;
		else
		{
			recount = 0;
			is_electric_right = false;
		}
	}
	if (is_electric_left)
	{
		App->renderer->Blit(sprites, 95, 546, &electric_left);
		if (lecount < 20) ++lecount;
		else
		{
			lecount = 0;
			is_electric_left = false;
		}
	}
	if (is_p25)
	{
		App->renderer->Blit(sprites, 102, 518, &p25);
		App->renderer->Blit(sprites, 276, 518, &p25);
		if (p25count < 100) ++p25count;
		else
		{
			bls++;
			p25count = 0;
			is_p25 = false;
		}
	}
	if (is_p50)
	{
		App->renderer->Blit(sprites, 75, 494, &p50);
		App->renderer->Blit(sprites, 305, 493, &p50);
		if (p50count < 100) ++p50count;
		else
		{
			bls++;
			p50count = 0;
			is_p50 = false;
		}
	}

	// Reset balls
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		App->player->ball->body->SetLinearVelocity(b2Vec2(0, 0));
		App->player->ball->body->SetAngularVelocity(0.0f);
		App->audio->PlayFx(secret2);
		App->player->ball->SetPosition(b2Vec2(App->player->ball_starting_pos.x, App->player->ball_starting_pos.y));
		pts = 0;
		bls = 5;
		// max_pts = 0;
	}

	if(rcount != 0 && ucount != 0 && lcount != 0)
	{
		pts += 25;
		is_p25 = true;
		App->audio->PlayFx(t1ah);
	}

	// pts - max_pts
	if (max_pts < pts)
	{
		max_pts = pts;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if ((bodyA == deathZone && bodyB == App->player->ball) && bls > 0)
	{
		bls--;
	}

	// Bouncers
	if (bodyA == middleBouncerLeft && bodyB == App->player->ball)
	{
		App->audio->PlayFx(bounce);
		is_bouncer_left = true;
		pts += 10;
	}
	else if (bodyA == middleBouncerUp && bodyB == App->player->ball)
	{
		App->audio->PlayFx(bounce);
		is_bouncer_up = true;
		pts += 10;
	}
	else if (bodyA == middleBouncerRight && bodyB == App->player->ball)
	{
		App->audio->PlayFx(bounce);
		is_bouncer_right = true;
		pts += 10;
	}

	// Electric bouncers
	if (bodyA == leftBouncer && bodyB == App->player->ball)
	{
		App->audio->PlayFx(electric_effect);
		is_electric_left = true;
	}
	else if (bodyA == rightBouncer && bodyB == App->player->ball)
	{
		App->audio->PlayFx(electric_effect);
		is_electric_right = true;
	}

	// Mini bouncers
	if (bodyA == miniBouncerLeft && bodyB == App->player->ball)
	{
		App->audio->PlayFx(mini_bounce);
	}
	else if (bodyA == miniBouncerTop && bodyB == App->player->ball)
	{
		App->audio->PlayFx(mini_bounce);
	}
	else if (bodyA == miniBouncerRight_1 && bodyB == App->player->ball)
	{
		App->audio->PlayFx(mini_bounce);
	}
	else if (bodyA == miniBouncerRight_2 && bodyB == App->player->ball)
	{
		App->audio->PlayFx(mini_bounce);
	}

	// Grind sensor
	if (bodyA == grind_sensor && bodyB == App->player->ball)
	{
		App->audio->PlayFx(secret);
		pts += 50;
		is_p50 = true;
	}
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

	int mini_bouncer_top[14] = {
		101, 156,
		104, 158,
		109, 159,
		114, 158,
		120, 155,
		125, 150,
		125, 144
	};

	int mini_bouncer_right[12] = {
		366, 248,
		361, 251,
		359, 256,
		359, 268,
		362, 273,
		367, 275
	};

	int mini_bouncer_left[12] = {
		84, 360,
		91, 361,
		96, 365,
		99, 372,
		100, 378,
		97, 384
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
	leftBouncer->SetBounce(1.8f); // Add more bounce
	leftBouncer->listener = this;

	rightBouncer = App->physics->CreateChain(167, 308, right_bouncer, 6, b2_staticBody);
	rightBouncer->SetBounce(1.8f); // Add more bounce
	rightBouncer->listener = this;

	/* Middle bouncers */
	middleBouncerLeft = App->physics->CreateCircle(187, 255, 24, b2_staticBody);
	middleBouncerLeft->SetBounce(1.8f);
	middleBouncerLeft->listener = this;

	middleBouncerUp = App->physics->CreateCircle(243, 190, 24, b2_staticBody);
	middleBouncerUp->SetBounce(1.8f);
	middleBouncerUp->listener = this;

	middleBouncerRight = App->physics->CreateCircle(289, 258, 24, b2_staticBody);
	middleBouncerRight->SetBounce(1.8f);
	middleBouncerRight->listener = this;

	/* Mini bouncers */
	miniBouncerTop = App->physics->CreateChain(-14, -10, mini_bouncer_top, 14, b2_staticBody, false);
	miniBouncerTop->SetBounce(1.8f);
	miniBouncerTop->listener = this;

	miniBouncerRight_1 = App->physics->CreateChain(-13, -9, mini_bouncer_right, 12, b2_staticBody, false);
	miniBouncerRight_1->SetBounce(1.8f);
	miniBouncerRight_1->listener = this;

	miniBouncerRight_2 = App->physics->CreateChain(-26, 180, mini_bouncer_right, 12, b2_staticBody, false);
	miniBouncerRight_2->SetBounce(1.8f);
	miniBouncerRight_2->listener = this;

	miniBouncerLeft = App->physics->CreateChain(-13, -6, mini_bouncer_left, 12, b2_staticBody, false);
	miniBouncerLeft->body->GetFixtureList()->SetRestitution(1.8f);
	miniBouncerLeft->listener = this;

	/* Little bouncers */
	littleBouncerLeft = App->physics->CreateRectangle(61, 640, 14, 3, b2_staticBody);
	littleBouncerLeft->SetBounce(1.8f);
	littleBouncerLeft->listener = this;

	littleBouncerRight = App->physics->CreateRectangle(353, 640, 14, 3, b2_staticBody);
	littleBouncerRight->SetBounce(1.8f);
	littleBouncerRight->listener = this;

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

	grind_sensor = App->physics->CreateCircle(355, 135, 15, b2_staticBody, true);
	grind_sensor->listener = this;

	deathZone = App->physics->CreateRectangle(205, 712, 112, 6, b2_staticBody, true);
	deathZone->listener = this;
}