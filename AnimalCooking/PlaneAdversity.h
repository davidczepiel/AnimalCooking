#pragma once
#include "Adversity.h"
#include "SDL_macros.h"
#include "Texture.h"

class PlaneAdversity : public Adversity
{
	Texture* planeTexture;
	SDL_Rect planeRect;
	float velocity;
	float force;

public:
	PlaneAdversity() : Adversity() {
		
	}
	~PlaneAdversity() {}
	
	void update();
	void draw();
	void reset();

};

