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

	SDL_Texture* flipper_texture;
	SDL_Rect left_flipper_rect;
};