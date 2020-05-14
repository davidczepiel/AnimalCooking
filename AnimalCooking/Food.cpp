#include "Food.h"
#include "SDL_macros.h"
#include "PlayState.h"
#include "FSM.h"
#include "TimerViewer.h"
#include "Entity.h"

Food::Food(Vector2D position, Resources::FoodType type, Transport* p1, Transport* p2) : Pickable(p1, p2, nullptr),
	timer_(new FoodTimer()),canDraw(true),
	type_(type),
	foodPool_(nullptr),
	texture_(nullptr)
{	
	position_ = position;
	size_ = Vector2D(SDLGame::instance()->getCasillaX()/2, SDLGame::instance()->getCasillaY()/2);
	speed_ = Vector2D();

	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(timer_);
}

Food::Food(Resources::FoodType type) : Pickable(nullptr, nullptr, nullptr),
	timer_(new FoodTimer()),
	type_(type),
	foodPool_(nullptr), 
	canDraw(true)
{
	position_ = Vector2D();
	size_ = Vector2D(SDLGame::instance()->getCasillaX() / 2, SDLGame::instance()->getCasillaY() / 2);
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

void Food::onDrop(bool onfloor)
{
	if (onfloor) {
		Pickable::onDrop(onfloor);
		timer_->timerStart();
				SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Drop,0);
	}
}

void Food::onFloor()
{
	//El gameControl llamaba al m�todo onDrop pero siempre con true, se necesita hacer est� distinci�n
	//porque sino el gameControl al generar una comida desencadena que se reproduzca el sonido de dejar caer cuando no deber�a
	Pickable::onDrop(true);
	timer_->timerStart();
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
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
}


