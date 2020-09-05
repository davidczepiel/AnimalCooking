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
	void start();

private:
	void lightingUpdate();
	void rainFrameUpdate();
	void rainUpdate();

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

	//-----------RAYOS---------
	Texture* lightingTexture_;
	Texture* explosionTexture_;
	bool lightingStrike_, lightingStrikeDone_, explosionDone_;
	int lightingFrameCadence_;
	int lastLightingFrame_;
	int explosionFrameCadence_;
	int lastExplosionFrame_;
	int maxLights;
	int numLights;
	Uint32 lastLightingTick_;
	Uint32 lastExplosionTick_;
	bool firstTimeLighting;

	vector<SDL_Rect> rectLighting_;
	vector<std::pair<Vector2D, bool>> lightingSpots_;
};

