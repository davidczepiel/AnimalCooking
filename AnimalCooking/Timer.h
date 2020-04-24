#pragma once
#include <SDL_stdinc.h>
#include "SDLGame.h"
#include "Texture.h"
#include "Vector2D.h"

class Timer {
public:
	Timer();
	~Timer();
	virtual void update();
	virtual void draw();

	void setTime(Uint32 t) { time_ = t; };	
	void setTexture(Texture* t) { texture_ = t; };
	void setPos(Vector2D p) { pos_ = p; };
	void setSize(Vector2D s) { size_ = s; };
	void setRot(double r) { rot_ = r; };
	
	Uint32 getTime() { return time_; };
	bool isTimerEnd() { return timerEnd_; };

	void timerStart();
	void timerReset();
	void timerPause();
	void timerResume();

	double getProgress() { return (game_->getTime() - startedTime_) / (double)time_; }

protected:
	SDLGame* game_;
	Texture* texture_;

	Uint32 time_;
	Uint32 startedTime_;
	Uint32 pausedTime_;

	bool timerStarted_;
	bool timerEnd_;
	

	Vector2D pos_;
	Vector2D size_;
	double rot_;
};

class FoodTimer : public Timer {
public:
	FoodTimer() : Timer() { time_ = 5000; }
	void draw() {}
};