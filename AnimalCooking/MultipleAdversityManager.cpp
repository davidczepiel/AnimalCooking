#include "MultipleAdversityManager.h"
#include "BurnedCookerAdversity.h"
#include "PlaneAdversity.h"
#include "HookAdversity.h"
#include "RainAdversity.h"
#include "GPadController.h"


MultipleAdversityManager::MultipleAdversityManager(Transform* tp1, Transform* tp2, CookerPool* cp, IngredientsPool* ip, UtensilsPool* up) : 
	Component(ecs::AdversityManager),
	tP1_(tp1), 
	tP2_(tp2), 
	cookerPool_(cp), 
	ingredientsPool_(ip), 
	utensilsPool_(up), 
	active_(false), 
	playingWarning_(false), 
	playingAdversity_(false),
	warningRate_(100), 
	justStarted_(true), 
	lengthOfRumble_(100), 
	rumbleCadence_(333),
	finishedAdversities(false)
	{
		warningTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::WarningAdversity);

		adversityTimer_ = new AdversityTimer();
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(adversityTimer_);

		adversities_.push_back(new PlaneAdversity(this));
		adversities_.push_back(new BurnedCookerAdversity(this));
		adversities_.push_back(new HookAdversity(this));
		adversities_.push_back(new RainAdversity(this));

		for (int i = 0; i < adversities_.size(); ++i) activeAdversities_.push_back(false);

		nextAdversityTimer_ = new AdversityTimer();
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(nextAdversityTimer_);
		nextWarningTimer_ = new AdversityTimer();
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(nextWarningTimer_);
}

void MultipleAdversityManager::update()
{
	if (finishedAdversities) return;	

	if (justStarted_) {
		startAdvesities();
		justStarted_ = false;
		return;
	}

	seeTimers();
	seeAdversityWarning();

	for (int i = 0; i < activeAdversities_.size(); ++i) {
		if (activeAdversities_[i])
			adversities_[i]->update();
	}
}

void MultipleAdversityManager::seeAdversityWarning() {
	nextWarningTimer_->update();
	if (nextWarningTimer_->isTimerEnd()) {
		nextWarningTimer_->timerReset();
		playingWarning_ = true;
		adversityTimer_->timerReset();
		adversityTimer_->setTime(warningRate_);
		adversityTimer_->timerStart();
		startRumbleTime_ = SDL_GetTicks();
	}

	if (playingWarning_) {
		adversityTimer_->update();
		if (SDL_GetTicks() - startRumbleTime_ > rumbleCadence_) {
			playRumbles();
			startRumbleTime_ = SDL_GetTicks();
		}
		if (adversityTimer_->isTimerEnd()) {
			if (active_) active_ = false;
			else active_ = true;

			adversityTimer_->timerReset();
			adversityTimer_->setTime(warningRate_);
			adversityTimer_->timerStart();
		}
	}
}

void MultipleAdversityManager::playRumbles()
{
	bool work = true;
	if (GPadController::instance()->playerControllerConnected(0)) {
		haptic1 = SDL_HapticOpen(0);
		if (haptic1 == NULL)
			work = false;
		if (work && SDL_HapticRumbleInit(haptic1) != 0)
			work = false;
		if (work && SDL_HapticRumblePlay(haptic1, 0.25, lengthOfRumble_) != 0)
			work = false;
	}
	work = true;
	if (GPadController::instance()->playerControllerConnected(1)) {
		haptic2 = SDL_HapticOpen(1);
		if (haptic2 == NULL)
			work = false;
		if (work && SDL_HapticRumbleInit(haptic2) != 0)
			work = false;
		if (work && SDL_HapticRumblePlay(haptic2, 0.25, lengthOfRumble_) != 0)
			work = false;
	}
}

void MultipleAdversityManager::seeTimers() {
	nextAdversityTimer_->update();
	if (nextAdversityTimer_->isTimerEnd() && !adversitiesQueue_.empty()) {
		activeAdversities_.at(std::get<1>(adversitiesQueue_.front())) = true;
		adversities_.at(std::get<1>(adversitiesQueue_.front()))->reset();
		playingWarning_ = false;
		active_ = false;
		adversitiesQueue_.pop();

		nextAdversityTimer_->timerReset();
		nextAdversityTimer_->setTime(std::get<0>(adversitiesQueue_.front()));
		nextAdversityTimer_->timerStart();

		nextWarningTimer_->timerReset();
		nextWarningTimer_->setTime(std::get<0>(adversitiesQueue_.front()) - 2000);
		nextWarningTimer_->timerStart();
	}

}

void MultipleAdversityManager::draw()
{
	if (finishedAdversities) return;

	for (int i = 0; i < activeAdversities_.size(); ++i) {
		if (activeAdversities_[i]) adversities_[i]->draw();
	}
	if (active_) warningTexture_->render(RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight()));
}

void MultipleAdversityManager::startAdvesities()
{
	if (adversitiesQueue_.empty()) return;

	nextWarningTimer_->timerReset();
	nextWarningTimer_->setTime(std::get<0>(adversitiesQueue_.front()) - 2000);
	nextWarningTimer_->timerStart();

	nextAdversityTimer_->timerReset();
	nextAdversityTimer_->setTime(std::get<0>(adversitiesQueue_.front()));
	nextAdversityTimer_->timerStart();
}

void MultipleAdversityManager::stopAdversity(ecs::AdversityID i)
{
	activeAdversities_[i] = false;

	if (!adversitiesQueue_.empty()) return;

	for (int i = 0; i < activeAdversities_.size(); ++i) {
		if (activeAdversities_[i]) return;
	}
	
	finishedAdversities = true;
}

void MultipleAdversityManager::addAdversityToQueue(ecs::AdversityID type, int time)
{
	adversitiesQueue_.push(tuple<int, ecs::AdversityID>(time, type));
}
