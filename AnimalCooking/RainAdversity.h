#pragma once
#include "Adversity.h"
#include "Texture.h"
#include "SDLGame.h"
#include "Timer.h"
#include "UtensilsPool.h"
#include "Collisions.h"
#include "SDL_macros.h"
class RainAdversity :public Adversity
{
public:
	RainAdversity(MultipleAdversityManager* mam);
	virtual void update();
	virtual void draw();
	virtual void reset();

private:
	Texture* rainTexture_;
	Timer* rainTimer_;	
	vector<Utensil*>* utensilsPool_;
	SDL_Rect drawingArea_;
	SDL_Rect clipArea_;

	double dirtSpeedUp_;
	int frameTime_;
	int lastFrame_;
	int animationFrame_;	
	int lastTick_;
	int cadence_;
	bool started_;
};

