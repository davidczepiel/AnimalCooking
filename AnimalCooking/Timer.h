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
	virtual void draw() = 0;

	void setTime(Uint32 t) { time_ = t; };	
	void setTexture(Texture* t) { texture_ = t; };
	void setPos(Vector2D p) { pos_ = p; };
	void setSize(Vector2D s) { size_ = s; };
	void setRot(double r) { rot_ = r; };
	
	Uint32 getTime() { return time_; };
	bool isTimerEnd() { return timerEnd_; };

	void timerStart();
	void timerReset();

protected:
	SDLGame* game_;
	Texture* texture_;

	Uint32 time_;
	Uint32 startedTime_;

	bool timerStarted_;
	bool timerEnd_;
	
	Vector2D pos_;
	Vector2D size_;
	double rot_;
};

class LevelTimer : public Timer {
public:
	LevelTimer() : Timer(), outlineText_(nullptr) {}
	LevelTimer(Uint32 lvlT) : Timer() { time_ = lvlT; outlineText_ = game_->getTextureMngr()->getTexture(Resources::RectangleOutline);}
	void draw();

	void update() {
		Timer::update();
		if (timerEnd_) {
			//Fin nivel
		}
	}

private:
	Texture* outlineText_;
};

class DefaultTimer : public Timer {
public:
	DefaultTimer() : Timer() { texture_ = game_->getTextureMngr()->getTexture(Resources::CuadradoAux); }
	DefaultTimer( Uint32 time ) : Timer() { time_ = time; texture_ = game_->getTextureMngr()->getTexture(Resources::CuadradoAux); }
	void draw();
	void update();
};

class FoodTimer : public Timer {
public:
	FoodTimer() : Timer() { time_ = 5000; }
	void draw() {}
};

class CookerTimer : public Timer {
public:
	CookerTimer() : Timer() { texture_ = game_->getTextureMngr()->getTexture(Resources::CircularTimer); size_ = Vector2D(50, 50); }
	CookerTimer(Uint32 ckT) : Timer() { time_ = ckT; texture_ = game_->getTextureMngr()->getTexture(Resources::CircularTimer); size_ = Vector2D(50, 50); }
	void draw();

	void update() {
		Timer::update();
		if (timerEnd_) {
			//Cocinar ingredientes
		}
	}

};