#pragma once
#include "Adversity.h"
#include "Texture.h"
#include "Timer.h"
#include "Utensil.h"
#include "SDL_macros.h"
#include "SDLGame.h"

class PidgeonAdversity :
	public Adversity
{

public:
	PidgeonAdversity(MultipleAdversityManager* mam);
	virtual void update();
	virtual void draw();
	virtual void reset() {};
	void start() {};
private:
	Texture* pidgeonTexture_;
	Timer* durationTimer_;

	SDL_Rect drawingArea_;
	SDL_Rect clipArea_;
};

