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
	warningRate_(100), 
	justStarted_(true), 
	lengthOfRumble_(100), 
	rumbleCadence_(333)	{
		adversities_.push_back(new PlaneAdversity(this));
		adversities_.push_back(new BurnedCookerAdversity(this));
		adversities_.push_back(new HookAdversity(this));
		adversities_.push_back(new RainAdversity(this));

		warningTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::WarningAdversity);

		rainTimer_ = new AdversityTimer();
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(rainTimer_);
		rainWarning_ = new AdversityTimer();
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(rainWarning_);
		planeTimer_ = new AdversityTimer();
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(planeTimer_);
		planeWarning_ = new AdversityTimer();
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(planeWarning_);
		hookTimer_ = new AdversityTimer();
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(hookTimer_);
		hookWarning_ = new AdversityTimer();
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(hookWarning_);
		burnCookerTimer_ = new AdversityTimer();
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(burnCookerTimer_);
		burnedCookerWarning_ = new AdversityTimer();
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(burnedCookerWarning_);
		adversityTimer_ = new AdversityTimer();
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(adversityTimer_);

		for (int i = 0; i < 4; ++i) activeAdversities_.push_back(false);
}

void MultipleAdversityManager::update()
{
	if (justStarted_) {
		startAdvesities();
		justStarted_ = false;
		return;
	}

	seeTimers();
	seeAdversityWarning();

	for (int i = 0; i < activeAdversities_.size(); ++i) {
		if (activeAdversities_[i]) adversities_[i]->update();
	}
}

void MultipleAdversityManager::seeAdversityWarning() {
	planeWarning_->update();
	if (planeWarning_->isTimerEnd()) {
		planeWarning_->timerReset();
		playingWarning_ = true;
		adversityTimer_->timerReset();
		adversityTimer_->setTime(warningRate_);
		adversityTimer_->timerStart();
		startRumbleTime_ = SDL_GetTicks();
	}
	hookWarning_->update();
	if (hookWarning_->isTimerEnd()) {
		hookWarning_->timerReset();
		playingWarning_ = true;
		adversityTimer_->timerReset();
		adversityTimer_->setTime(warningRate_);
		adversityTimer_->timerStart();
		startRumbleTime_ = SDL_GetTicks();
	}
	rainWarning_->update();
	if (rainWarning_->isTimerEnd()) {
		rainWarning_->timerReset();
		playingWarning_ = true;
		adversityTimer_->timerReset();
		adversityTimer_->setTime(warningRate_);
		adversityTimer_->timerStart();
		startRumbleTime_ = SDL_GetTicks();
	}
	burnedCookerWarning_->update();
	if (burnedCookerWarning_->isTimerEnd()) {
		burnedCookerWarning_->timerReset();
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
	planeTimer_->update();

	if (planeTimer_->isTimerEnd()) {
		planeTimer_->timerReset();
		activeAdversities_.at(ecs::AdversityID::PlaneAdversity) = true;
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::PlaneSound, 0, -1);
		adversities_.at(ecs::AdversityID::PlaneAdversity)->reset();
		playingWarning_ = false;
		active_ = false;
		if (!planeQueue.empty()) {
			setTimerTime(ecs::AdversityID::PlaneAdversity, planeQueue.front());
			planeQueue.pop();
		}
	}

	hookTimer_->update();

	if (hookTimer_->isTimerEnd()) {
		hookTimer_->timerReset();
		activeAdversities_.at(ecs::AdversityID::HookAdversity) = true;
		adversities_.at(ecs::AdversityID::HookAdversity)->reset();
		playingWarning_ = false;
		active_ = false;
		if (!hookQueue.empty()) {
			setTimerTime(ecs::AdversityID::HookAdversity, hookQueue.front());
			hookQueue.pop();
		}
	}

	rainTimer_->update();

	if (rainTimer_->isTimerEnd()) {
		rainTimer_->timerReset();
		activeAdversities_.at(ecs::AdversityID::RainAdversity) = true;
		adversities_.at(ecs::AdversityID::RainAdversity)->reset();
		playingWarning_ = false;
		active_ = false;
		if (!rainQueue.empty()) {
			setTimerTime(ecs::AdversityID::RainAdversity, rainQueue.front());
			rainQueue.pop();
		}
	}

	burnCookerTimer_->update();

	if (burnCookerTimer_->isTimerEnd()) {
		burnCookerTimer_->timerReset();
		activeAdversities_.at(ecs::AdversityID::CookersAdversity) = true;
		adversities_.at(ecs::AdversityID::CookersAdversity)->reset();
		playingWarning_ = false;
		active_ = false;
		if (!cookerQueue.empty()) {
			setTimerTime(ecs::AdversityID::CookersAdversity, cookerQueue.front());
			cookerQueue.pop();
		}
	}

}

void MultipleAdversityManager::draw()
{
	for (int i = 0; i < activeAdversities_.size(); ++i) {
		if (activeAdversities_[i]) adversities_[i]->draw();
	}
	if (active_) warningTexture_->render(RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight()));
}

void MultipleAdversityManager::startAdvesities()
{
	if (!planeQueue.empty()) { setTimerTime(ecs::AdversityID::PlaneAdversity, planeQueue.front()); planeQueue.pop(); }
	if (!rainQueue.empty()) { setTimerTime(ecs::AdversityID::RainAdversity, rainQueue.front()); rainQueue.pop(); }
	if (!cookerQueue.empty()) { setTimerTime(ecs::AdversityID::CookersAdversity, cookerQueue.front()); cookerQueue.pop(); }
	if (!hookQueue.empty()) { setTimerTime(ecs::AdversityID::HookAdversity, hookQueue.front()); hookQueue.pop(); }
}

void MultipleAdversityManager::stopAdversity(ecs::AdversityID i)
{
	activeAdversities_[i] = false;
}

void MultipleAdversityManager::setTimerTime(ecs::AdversityID id, int time)
{
	switch (id) {
	case ecs::AdversityID::RainAdversity:
		rainWarning_->timerReset();
		rainWarning_->setTime(time);
		rainWarning_->timerStart();
		rainTimer_->timerReset();
		rainTimer_->setTime(time + 2000);
		rainTimer_->timerStart();
		break;
	case ecs::AdversityID::HookAdversity:
		hookWarning_->timerReset();
		hookWarning_->setTime(time);
		hookWarning_->timerStart();
		hookTimer_->timerReset();
		hookTimer_->setTime(time + 2000);
		hookTimer_->timerStart();
		break;
	case ecs::AdversityID::PlaneAdversity:
		planeWarning_->timerReset();
		planeWarning_->setTime(time);
		planeWarning_->timerStart();
		planeTimer_->timerReset();
		planeTimer_->setTime(time + 2000);
		planeTimer_->timerStart();
		break;
	case ecs::AdversityID::CookersAdversity:
		burnCookerTimer_->timerReset();
		burnedCookerWarning_->setTime(time);
		burnedCookerWarning_->timerStart();
		burnCookerTimer_->timerReset();
		burnCookerTimer_->setTime(time + 2000);
		burnCookerTimer_->timerStart();
		break;
	}
}

void MultipleAdversityManager::addAdversityToQueue(ecs::AdversityID type, int time)
{
	switch (type)
	{
	case ecs::AdversityID::PlaneAdversity:
		planeQueue.push(time);
		break;
	case ecs::AdversityID::RainAdversity:
		rainQueue.push(time);
		break;
	case ecs::AdversityID::HookAdversity:
		hookQueue.push(time);
		break;
	case ecs::AdversityID::CookersAdversity:
		cookerQueue.push(time);
		break;
	default:
		break;
	}
}
