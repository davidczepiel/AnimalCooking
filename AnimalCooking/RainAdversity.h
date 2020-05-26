#pragma once
#include "Adversity.h"
#include "Texture.h"
#include "SDLGame.h"
#include "Timer.h"
#include "UtensilsPool.h"
#include "Collisions.h"
#include "SDL_macros.h"
class RainAdversity :
	public Adversity
{

	Texture* rainTexture;
	SDL_Rect drawingArea;
	SDL_Rect clipArea;
	vector<Utensil*>* utensilsPool;
	double dirtSpeedUp;
	Timer* rainTimer;
	int frameTime;
	int lastFrame;
	int animationFrame;
	bool started;
	int lastTick;
	int cadence;
	

public:
	RainAdversity(MultipleAdversityManager* mam);
	virtual void update();
	virtual void draw();
	virtual void reset();

};

