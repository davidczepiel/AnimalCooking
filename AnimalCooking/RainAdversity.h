#pragma once
#include "Adversity.h"
#include "Texture.h"
#include "SDLGame.h"
#include "Timer.h"
#include "UtensilsPool.h"
#include "Collisions.h"
class RainAdversity :
	public Adversity
{

	Texture* rainTexture;
	SDL_Rect drawingArea;
	SDL_Rect clipArea;
	vector<Utensil*>* utensilsPool;
	double dirtSpeedUp;
	Timer rainTimer;
	int frameTime;
	int lastFrame;
	int animationFrame;
	bool started;

public:
	RainAdversity(AdversityManager* am, MultipleAdversityManager* mam);
	virtual void update();
	virtual void draw();
	virtual void reset();

};

