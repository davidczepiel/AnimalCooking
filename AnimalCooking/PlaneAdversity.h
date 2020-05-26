#pragma once
#include "Adversity.h"
#include "SDL_macros.h"
#include "Texture.h"
#include "AdversityManager.h"
#include "MultipleAdversityManager.h"
#include "TimerViewer.h"

class PlaneAdversity : public Adversity
{
	enum state : int { Pasando, Empujando};

	Texture* planeTexture_;
	SDL_Rect planeRect_;
	int velocity_;
	float force_;
	vector<Vector2D> dirs_{Vector2D(1, 0), Vector2D(-1, 0), Vector2D(0, 1), Vector2D(0, -1), Vector2D(1, 1), Vector2D(-1, 1), Vector2D(1, -1), Vector2D(-1, -1) };
	vector<double> angles_{90.0, -90.0, 180, 0, 135, 225, 45, -45 };
	Vector2D dir_;
	double angle_;
	Timer* internalTimer;
	state state_;
	bool alreadyInitialized;

	void StartPlane();
	bool isPlaneOut();
public:
	PlaneAdversity(AdversityManager* am, MultipleAdversityManager* mam) : Adversity(am, mam), internalTimer(new Timer()), alreadyInitialized(false) { }
	~PlaneAdversity() { delete internalTimer; }
	
	void update();
	void draw();
	void reset();
};

