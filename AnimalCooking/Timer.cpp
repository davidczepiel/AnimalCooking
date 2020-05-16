#include "Timer.h"
#include "SDL_macros.h"
#include "FSM.h";
#include "PlayState.h"
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
	}
}

void DefaultTimer::draw() {
	SDL_Rect rect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());
	texture_->render(rect);
}

void DefaultTimer::update()
{
	Timer::update();
	size_.setX((game_->getTime() - startedTime_) / 100);
}


void Timer::timerStart() {
	if (!timerStarted_) {
		timerStarted_ = true;
		startedTime_ = game_->getTime();
		timerEnd_ = false;
	} 
}

void Timer::timerReset() {
	startedTime_ = 0;
	timerStarted_ = false;
	timerEnd_ = false;
}

void Timer::timerPause()
{
	if (timerStarted_) {
		pausedTime_ = SDLGame::instance()->getTime() - startedTime_;
		timerStarted_ = false;
	}
}

void Timer::timerResume()
{
	if (pausedTime_ != 0) {
		startedTime_ = SDLGame::instance()->getTime() - pausedTime_;
		pausedTime_ = 0;
		timerStarted_ = true;
	}
}
void LevelTimer::draw()
{
	SDL_Rect rect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());
	outlineText_->render(rect);

	double percent = (game_->getTime() - startedTime_) / double(time_);

	rect.x = pos_.getX(); rect.y = pos_.getY(); rect.w = size_.getX() * (1 - percent); rect.h = size_.getY();

	SDL_Rect clip = SDL_Rect();
	clip.x = 0; clip.y = 0; clip.w = rect.w; clip.h = rect.h;

	texture_->render(rect, 0, clip);
}

void LevelTimer::update()
{
	Timer::update();

	if (timerEnd_) {
		timerReset();
		PlayState* p = static_cast<PlayState*> (SDLGame::instance()->getFSM()->currentState());
		p->goToEndState(p->getAnimalCooking());
		//Fin nivel
	}
}

void CookerTimer::draw()
{
	SDL_Rect destRect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());
	int col = (((game_->getTime() - startedTime_) * texture_->getNumCols()) / time_);
	texture_->renderFrame(destRect, 0, col, 0);
}
