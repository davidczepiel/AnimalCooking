#include "Food.h"
#include "SDL_macros.h"

Food::Food(Vector2D position, Resources::FoodType type, Transport* p1, Transport* p2) : Pickable(p1, p2, nullptr),
	timer_(FoodTimer()),
	type_(type),
	foodPool_(nullptr),
	texture_(nullptr)
{	
	position_ = position;
	size_ = Vector2D(64, 64);
	speed_ = Vector2D();
}

Food::Food(Resources::FoodType type) : Pickable(nullptr, nullptr, nullptr),
	type_(type),
	foodPool_(nullptr)
{
	position_ = Vector2D();
	size_ = Vector2D(50, 50);
	speed_ = Vector2D();
}

void Food::setFoodPool(FoodPool* foodPool, std::vector<Food*>::iterator it)
{
	foodPool_ = foodPool;
	iterator_ = it;
}

void Food::Destroy()
{
	foodPool_->RemoveFood(iterator_);
}

void Food::update()
{
	Pickable::update();

	if (timer_.isTimerEnd()) {
		foodPool_->RemoveFood(iterator_);
	}
	else {
		timer_.update();
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
		onFloor();
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Drop,0);
	}
}

void Food::onFloor()
{
	//El gameControl llamaba al método onDrop pero siempre con true, se necesita hacer está distinción
	//porque sino el gameControl al generar una comida desencadena que se reproduzca el sonido de dejar caer cuando no debería
	Pickable::onDrop(true);
	timer_.timerStart();
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

void Food::feedback()
{
	SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
	feedbackVisual_->render(destRect);
}

void Food::onPick() {
	timer_.timerReset();
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
}


