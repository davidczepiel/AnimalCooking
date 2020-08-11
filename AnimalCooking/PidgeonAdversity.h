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
	virtual void reset() ;
	void start() ;
private:

	bool hasReached(double d);
	Texture* pidgeonStandingTexture_;
	Texture* pidgeonFlyingTexture_;
	Texture* drawingTexture_;
	Timer* durationTimer_;

	bool coming_;
	bool standing_;
	bool leaving_;

	int row;
	int column;
	int lastFrame;
	int frameDuration;

	SDL_Rect drawingArea_;
	SDL_Rect clipArea_;
};

