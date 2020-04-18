#include "Timer.h"
#include "SDL_macros.h"

Timer::Timer(): 
	game_(SDLGame::instance()),
	texture_(nullptr),
	time_(0),
	startedTime_(0),  
	timerEnd_(false), 
	timerStarted_(false),
	pos_(), 
	size_(Vector2D(0, 5)), 
	rot_(0)
{
}

Timer::~Timer() {
}

void Timer::update() {
	if (timerStarted_ && !timerEnd_) {
		if (game_->getTime() - startedTime_ >= time_) {
			timerEnd_ = true;
		}
		size_.setX((game_->getTime() - startedTime_)/100);
	}
}

void DefaultTimer::draw() {
	SDL_Rect rect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());
	texture_->render(rect);
}


void Timer::timerStart() {
	if (!timerStarted_) {
		timerStarted_ = true;
		startedTime_ = game_->getTime();
	} 
}

void Timer::timerReset() {
	startedTime_ = 0;
	timerStarted_ = false;
	timerEnd_ = false;
}

void LevelTimer::draw()
{
	SDL_Rect rect = RECT(pos_.getX(), pos_.getY(), time_ / 100, size_.getY());
	outlineText_->render(rect);

	rect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());
	texture_->render(rect);
}

void CookerTimer::draw()
{
	SDL_Rect destRect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());
	int col = 0 + (game_->getTime() - startedTime_) % texture_->getNumCols();
	texture_->renderFrame(destRect, 1, 1, 0);
}
