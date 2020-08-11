#pragma once
#include "Adversity.h"
#include "Texture.h"
#include "Timer.h"
#include "Utensil.h"
#include "SDL_macros.h"
#include "SDLGame.h"
#include <vector>

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
	void locatePidgeon();
	int posibleLocation(int a, int b);

	Texture* drawingTexture_;
	Timer* durationTimer_;

	vector<bool> positions;

	bool coming_;
	bool standing_;
	bool leaving_;

	int row;
	int column;
	int lastFrame;
	int frameDuration;
	int angle;

	SDL_Rect drawingArea_;
	SDL_Rect clipArea_;
};

