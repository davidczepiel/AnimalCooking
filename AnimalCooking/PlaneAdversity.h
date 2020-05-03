#pragma once
#include "Adversity.h"
#include "SDL_macros.h"
#include "Texture.h"
#include "AdversityManager.h"

class PlaneAdversity : public Adversity
{
	Texture* planeTexture_;
	SDL_Rect planeRect_;
	int velocity_;
	float force_;
	double angle;
	Vector2D dir_;

	void StartPlane();
	Vector2D calculateDir();

public:
	PlaneAdversity(AdversityManager* am, MultipleAdversityManager* mam) : Adversity(am, mam) { StartPlane(); }
	~PlaneAdversity() {}
	
	void update();
	void draw();
	void reset();
};

