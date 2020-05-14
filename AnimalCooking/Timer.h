#pragma once
#include <SDL_stdinc.h>
#include "SDLGame.h"
#include "Texture.h"
#include "Vector2D.h"
#include "ScoreManager.h"

class Timer {
public:
	Timer();
	~Timer();
	virtual void update();
	virtual void draw() {}

	void setTime(Uint32 t) { time_ = t; };	
	void setTexture(Texture* t) { texture_ = t; };
	void setPos(Vector2D p) { pos_ = p; };
	void setSize(Vector2D s) { size_ = s; };
	inline Vector2D getSize() { return size_; }
	void setRot(double r) { rot_ = r; };

	inline bool isStarted() { return timerStarted_; }
	
	Uint32 getTime() { return time_; };
	bool isTimerEnd() { return timerEnd_; };

	void timerStart();
	void timerReset();
	void timerPause();
	void timerResume();

	//De 0 a 1
	double getProgress() { return (game_->getTime() - startedTime_) / (double)time_; }
	int getElapsedMs() { return game_->getTime() - startedTime_; }

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

class LevelTimer : public Timer {
public:
	LevelTimer() : Timer(), outlineText_(game_->getTextureMngr()->getTexture(Resources::LevelTimerBackground)){
		texture_ = game_->getTextureMngr()->getTexture(Resources::LevelTimerForeground);
	}
	LevelTimer(Uint32 lvlT) : Timer(), outlineText_(game_->getTextureMngr()->getTexture(Resources::LevelTimerBackground)){
		time_ = lvlT;
		texture_ = game_->getTextureMngr()->getTexture(Resources::LevelTimerForeground);
	}
	void draw();
	void update();

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
};