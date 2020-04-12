#pragma once
#include "Adversity.h"
#include "Transform.h"
#include"Texture.h"
class HookAdversity :
	public Adversity
{
	Transform* tP1;
	Transform* tP2;
	Texture* hookTexture;
	SDL_Rect drawingAreaHook1;
	SDL_Rect drawingAreaHook2;
	SDL_Rect clipArea;
	bool catched;
	bool changedPositions;
	bool droped;

	int frameTime;
	int lastFrame;
	int animationFrame;
	int catchPlayerSpeed;
	int changePlayersSpeed;
	int player1YPosition;
	int player2YPosition;
	int hook1Vel;
	int hook2Vel;
	int lastTick;
	void Catching(int advancedTicks);
	void Lifting(int advancedTicks);
	void GoingDown(int advancedTicks);
public:
	HookAdversity(AdversityManager* am);
	virtual void update();
	virtual void draw();
	virtual void reset();
};

