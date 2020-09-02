#pragma once
#include "Adversity.h"
#include "SDL_macros.h"
#include "Texture.h"
#include "MultipleAdversityManager.h"
#include "TimerViewer.h"

class PlaneAdversity : public Adversity
{
public:
	PlaneAdversity(MultipleAdversityManager* mam);
	~PlaneAdversity() { delete internalTimer; }
	
	void update();
	void draw();
	void reset();
	void start();

	inline void setMode(bool mode) { isBlizzard_ = mode; }

private:
	enum state : int { Going, Pushing };

	void StartPlane();
	bool isPlaneOut();
	void moveEntities();

	Texture* planeTexture_;
	Texture* blizzardTexture_;
	Timer* internalTimer;
	vector<Vector2D> dirs_{ Vector2D(1, 0), Vector2D(-1, 0), Vector2D(0, 1), Vector2D(0, -1), Vector2D(1, 1), Vector2D(-1, 1), Vector2D(1, -1), Vector2D(-1, -1) };
	vector<double> angles_{ 90.0, -90.0, 180, 0, 135, 225, 45, -45 };
	Vector2D dir_;
	SDL_Rect planeRect_;	
	state state_;

	double angle_;
	float force_;
	int velocity_;	
	bool alreadyInitialized;

	bool isBlizzard_;
	Uint32 blizzardDuration_;
	Uint32 blizzardLastAnimTick_;
	int blizzardFrameRate_;
	int blizzardFrame_;
};

