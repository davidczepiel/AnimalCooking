#include "Food.h"
#include "SDL_macros.h"
#include "PlayState.h"
#include "FSM.h"
#include "TimerViewer.h"
#include "Entity.h"

Food::Food(Vector2D position, Resources::FoodType type, Transport* p1, Transport* p2) : Pickable(p1, p2, nullptr),
	timer_(new FoodTimer()),
	type_(type),
	foodPool_(nullptr),
	texture_(nullptr)
{	
	position_ = position;
	size_ = Vector2D(64, 64);
	speed_ = Vector2D();

	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(timer_);
}

Food::Food(Resources::FoodType type) : Pickable(nullptr, nullptr, nullptr),
	timer_(new FoodTimer()),
	type_(type),
	foodPool_(nullptr)
{
	position_ = Vector2D();
	size_ = Vector2D(50, 50);
	speed_ = Vector2D();

	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(timer_);
}

void Food::setFoodPool(FoodPool* foodPool, std::vector<Food*>::iterator it)
{
	foodPool_ = foodPool;
	iterator_ = it;
}

void Food::Destroy()
{
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->deleteTimer(timer_);
	foodPool_->RemoveFood(iterator_);
	dead = true;
}

void Food::update()
{
	Pickable::update();

	if (timer_->isTimerEnd()) {
		Destroy();
	}
	else {
		timer_->update();
	}
}

void Food::draw()
{
	SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
	texture_->render(destRect);
}

void Food::draw(SDL_Rect r)
{
	texture_->render(r);
}

void Food::onDrop(bool onFloor)
{
	if (onFloor) {
		Pickable::onDrop(onFloor);
		timer_->timerStart();
	}
}

void Food::action1(int player)
{
	if (player == Resources::Player1) {
		player1_->pick(this, Resources::PickableType::Food);
	}
	else {
		player2_->pick(this, Resources::PickableType::Food);
	}
}

void Food::feedback(int player)
{
	if (!dead && feedbackVisual_ != nullptr) {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		feedbackVisual_->render(destRect);
	}
}

void Food::onPick() {
	timer_->timerReset();
}


