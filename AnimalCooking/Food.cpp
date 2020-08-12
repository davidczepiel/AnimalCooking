#include "Food.h"
#include "SDL_macros.h"
#include "PlayState.h"
#include "FSM.h"
#include "TimerViewer.h"
#include "Entity.h"
#include "GPadController.h"

Food::Food(Vector2D position, Resources::FoodType type, Transport* p1, Transport* p2, Texture* explosion) : Pickable(p1, p2, nullptr),
timer_(new FoodTimer()),
canDraw(true),
type_(type),
foodPool_(nullptr),
texture_(nullptr),
showHelp(true),
explosion_(explosion),
explosionFrame_(),
lastFrameTime_()
{
	position_ = position;

	jute::jValue& jsonGeneral = SDLGame::instance()->getJsonGeneral();
	size_ = Vector2D(jsonGeneral["Foods"]["size"]["width"].as_double() * SDLGame::instance()->getCasillaX(), jsonGeneral["Foods"]["size"]["height"].as_double() * SDLGame::instance()->getCasillaY());
	speed_ = Vector2D();

	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(timer_);
}

Food::Food(Resources::FoodType type, Texture* explosion) : Pickable(nullptr, nullptr, nullptr),
timer_(new FoodTimer()),
type_(type),
foodPool_(nullptr),
canDraw(true),
showHelp(true),
explosion_(explosion),
explosionFrame_(),
lastFrameTime_()
{
	position_ = Vector2D();
	jute::jValue& jsonGeneral = SDLGame::instance()->getJsonGeneral();
	size_ = Vector2D(jsonGeneral["Foods"]["size"]["width"].as_double() * SDLGame::instance()->getCasillaX(), jsonGeneral["Foods"]["size"]["height"].as_double() * SDLGame::instance()->getCasillaY());
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

	timer_->update();
	if (timer_->isTimerEnd()) {
		Destroy();
	}
}

void Food::draw()
{
	SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
	texture_->render(destRect);
	if (explosion_ != nullptr && explosionFrame_ < explosion_->getNumCols())
	{
		int time = SDLGame::instance()->getTime();
		if (time - lastFrameTime_ >= 160)
		{
			explosionFrame_++;
			lastFrameTime_ = time;

		}
		destRect.w += .4 * destRect.w;
		destRect.x -= .15 * destRect.w;
		destRect.h += .2 * destRect.h;
		explosion_->renderFrame(destRect, 0, explosionFrame_, 0);
			/*if (explosionFrame_ == explosion_->getNumCols())
			{
				i->setHasToPlayExplosion(false);
				explosionFrame_ = 0;
			}*/
	}
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
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Drop, 0);
		showHelp = true;
		inHands = false;
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
	if (player == Resources::Player1)
	{
		if (!inHands) player1_->pick(this, Resources::PickableType::Food);
	}
	else
	{
		if (!inHands) player2_->pick(this, Resources::PickableType::Food);
	}
	showHelp = false;
}

void Food::feedback(int player)
{
	if (!inHands && !dead && feedbackVisual_ != nullptr) {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		feedbackVisual_->render(destRect);
		if (showHelp && SDLGame::instance()->getOptions().showKeyToPress) {
			if (GPadController::instance()->playerControllerConnected(player))
				SDLGame::instance()->renderFeedBack(position_, "Pick up", SDL_GameControllerGetStringForButton(SDLGame::instance()->getOptions().players_gPadButtons[player].PICKUP));
			else
				SDLGame::instance()->renderFeedBack(position_, "Pick up", SDL_GetKeyName(SDLGame::instance()->getOptions().players_keyboardKeys[player].PICKUP));
		}
	}
}

void Food::onPick() {
	inHands = true;
	timer_->timerReset();
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
}


