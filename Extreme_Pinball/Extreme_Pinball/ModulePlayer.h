#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

#include "SDL/include/SDL_rect.h"

class PhysBody;
struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	PhysBody* left_flipper;
	PhysBody* right_flipper;

	SDL_Texture* textures;
	SDL_Rect left_flipper_rect;
	SDL_Rect right_flipper_rect;

	int lifes;
	PhysBody* ball;
	SDL_Rect ball_rect;
};