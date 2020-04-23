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
	size_(), 
	rot_(0){
}

Timer::~Timer() {
}

void Timer::update() {
	if (timerStarted_ && !timerEnd_) {
		if (game_->getTime() - startedTime_ >= time_) {
			timerEnd_ = true;
		}
	}
}

void Timer::draw() {
	SDL_Rect rect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());

	texture_->render(rect, rot_);
}


void Timer::timerStart() {
	if (!timerStarted_) {
		timerStarted_ = true;
		startedTime_ = game_->getTime();
		cout << "STARTED TIME : " << startedTime_ << endl;
		cout << "TIME : " << time_ << endl;
	} 
}

void Timer::timerReset() {
	cout << "RESET TIME : " << startedTime_ << endl;
	startedTime_ = 0;
	timerStarted_ = false;
	timerEnd_ = false;
}

void Timer::timerPause()
{
	time_ = time_ - (SDLGame::instance()->getTime() - startedTime_);
	timerReset();
}
