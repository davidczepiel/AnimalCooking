#include "Cooker.h"
#include "SDLGame.h"
#include "SDL_macros.h"
#include "InsertExpel.h"
#include "TimerViewer.h"
#include "GameConfig.h"

Cooker::Cooker(Vector2D& pos, Vector2D& size, double rot, Texture* text, Transport* t1, Transport* t2,Entity* e) : Interactive(t1,t2,nullptr),
	state_(CookerStates::empty), cookingTime_(5), entity_(e), timer_(nullptr)
{
	setPos(pos);
	setSize(size);
	setRot(rot);

	feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Panel);
}

void Cooker::initTimer()
{
	timer_ = new CookerTimer(cookingTime_);

	timer_->setPos(Vector2D((position_.getX() + size_.getX() / 2) - timer_->getSize().getX() / 2,
		(position_.getY() + size_.getY() / 2) - timer_->getSize().getY() / 2));
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(timer_);
}

Cooker::~Cooker() {
	timer_ = nullptr;
}

void Cooker::setCookerState(CookerStates s) { 
	switch (s) {
		case CookerStates::empty:  setEmptyTexture(); break;
		case CookerStates::cooking: setCookingTexture(); break;
		case CookerStates::cooked:  setCookedTexture(); break;
		case CookerStates::burned:  setBurnedTexture(); break;
	}
	state_ = s; 
};

void Cooker::draw()
{
	SDL_Rect rect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());

	if (state_ == CookerStates::cooking) {
		int row = (timer_->getProgress() / (17 % texture_->getNumRows()));
		texture_->renderFrame(rect, row, 0, rotation_);
	}
	else texture_->render(rect, rotation_);
}

void Cooker::action1(int player)
{
	InsertExpel* ie = entity_->getComponent<InsertExpel>(ecs::InsertExpel);
	if (this->getCookerState() == CookerStates::empty)
	{
		ie->insertFood(this, player);
	}
	else 
	{
		ie->extractFood(this, timer_, player);
	}
}

void Cooker::feedback(int player)
{
	if (state_ != CookerStates::empty) {
		int ofset = 60;
		int offsetInside = 15;
		int rows = ceil(foods_.size() / 2.0);
		if (rows == 0) rows = 1;

		int w = 190/ 2 - offsetInside * 2;
		SDL_Rect rect = RECT(position_.getX() + ofset, position_.getY() + ofset, 190, rows*w + offsetInside*2);
		feedbackVisual_->render(rect);
		rect.x += offsetInside;
		rect.y += offsetInside;

		for (int i = 0; i < foods_.size(); ++i) {

			SDL_Rect r = { rect.x + w * (i % 2), rect.y + w * (i / 2), w, w };
			foods_[i]->draw(r);
		}
	}
}

void Cooker::sound()
{
	if (SDL_GetTicks() - lastTimeSound_ > 2000) {
		lastTimeSound_ = SDL_GetTicks();
		//Miro qu� tipo de cooker soy y reprocuzco un sonido u otro dependiendo de si he quemado algo o no 
		switch (cookerType_) {
		case Resources::Cookers::Skillet:
			if(state_ == CookerStates::cooking)SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::FrySound,0);
			else if(state_ == CookerStates::cooked) SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::FrySoundBurned, 0);
			break;
		case Resources::Cookers::Oven:
			if(state_ == CookerStates::cooking)SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::FrySound,0);
			else if (state_ == CookerStates::cooked)SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::FrySoundBurned, 0);
			break;
		}
	}
}

Skillet::Skillet(Vector2D& pos, Vector2D& size, double rot, Texture* text,Transport* t1,Transport* t2, Entity* e) : Cooker(pos, size, rot, text,t1,t2,e)
{
	cookingTime_ = config::SKILLET_SECONDS_TO_COOK * 1000;
	cookerType_ = Resources::Cookers::Skillet;
	initTimer();
	setEmptyTexture();
}

Oven::Oven(Vector2D& pos, Vector2D& size, double rot, Texture* text, Transport* t1, Transport* t2, Entity* e) : Cooker(pos, size, rot, text, t1, t2, e)
{
	cookingTime_ = config::OVEN_SECONDS_TO_COOK * 1000;
	cookerType_ = Resources::Cookers::Oven;
	initTimer();
	setEmptyTexture();
}