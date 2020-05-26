#include "MultipleAdversityManager.h"
#include "BurnedCookerAdversity.h"
#include "PlaneAdversity.h"
#include "HookAdversity.h"
#include "RainAdversity.h"
#include "GPadController.h"


MultipleAdversityManager::MultipleAdversityManager(Transform* tp1, Transform* tp2, CookerPool* cp, IngredientsPool* ip, UtensilsPool* up) : Component(ecs::AdversityManager),
tP1(tp1), tP2(tp2), cookerPool(cp), ingredientsPool(ip), utensilsPool(up), active(false), playingWarning(false), warningRate(100), justStarted(true), lengthOfRumble_(100), rumbleCadence(333)
{
	adversities.push_back(new PlaneAdversity(nullptr, this));
	adversities.push_back(new BurnedCookerAdversity(nullptr, this));
	adversities.push_back(new HookAdversity(nullptr, this));
	adversities.push_back(new RainAdversity(nullptr, this));

	warningTexture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::WarningAdversity);

	rainTimer = new AdversityTimer();
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(rainTimer);
	rainWarning = new AdversityTimer();
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(rainWarning);
	planeTimer = new AdversityTimer();
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(planeTimer);
	planeWarning = new AdversityTimer();
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(planeWarning);
	hookTimer = new AdversityTimer();
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(hookTimer);
	hookWarning = new AdversityTimer();
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(hookWarning);
	burnCookerTimer = new AdversityTimer();
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(burnCookerTimer);
	burnedCookerWarning = new AdversityTimer();
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(burnedCookerWarning);
	adversityTimer = new AdversityTimer();
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(adversityTimer);

	for (int i = 0; i < 4; ++i) activeAdversities.push_back(false);
}

void MultipleAdversityManager::update()
{
	if (justStarted) {
		startAdvesities();
		justStarted = false;
		return;
	}

	seeTimers();
	seeAdversityWarning();

	for (int i = 0; i < activeAdversities.size(); ++i) {
		if (activeAdversities[i]) adversities[i]->update();
	}
}

void MultipleAdversityManager::seeAdversityWarning() {
	planeWarning->update();
	if (planeWarning->isTimerEnd()) {
		planeWarning->timerReset();
		playingWarning = true;
		adversityTimer->timerReset();
		adversityTimer->setTime(warningRate);
		adversityTimer->timerStart();
		startRumbleTime_ = SDL_GetTicks();
	}
	hookWarning->update();
	if (hookWarning->isTimerEnd()) {
		hookWarning->timerReset();
		playingWarning = true;
		adversityTimer->timerReset();
		adversityTimer->setTime(warningRate);
		adversityTimer->timerStart();
		startRumbleTime_ = SDL_GetTicks();
	}
	rainWarning->update();
	if (rainWarning->isTimerEnd()) {
		rainWarning->timerReset();
		playingWarning = true;
		adversityTimer->timerReset();
		adversityTimer->setTime(warningRate);
		adversityTimer->timerStart();
		startRumbleTime_ = SDL_GetTicks();
	}
	burnedCookerWarning->update();
	if (burnedCookerWarning->isTimerEnd()) {
		burnedCookerWarning->timerReset();
		playingWarning = true;
		adversityTimer->timerReset();
		adversityTimer->setTime(warningRate);
		adversityTimer->timerStart();
		startRumbleTime_ = SDL_GetTicks();
	}

	if (playingWarning) {
		adversityTimer->update();
		if (SDL_GetTicks() - startRumbleTime_ > rumbleCadence) {
			playRumbles();
			startRumbleTime_ = SDL_GetTicks();
		}
		if (adversityTimer->isTimerEnd()) {
			if (active) active = false;
			else active = true;

			adversityTimer->timerReset();
			adversityTimer->setTime(warningRate);
			adversityTimer->timerStart();
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
	planeTimer->update();

	if (planeTimer->isTimerEnd()) {
		planeTimer->timerReset();
		activeAdversities.at(ecs::AdversityID::PlaneAdversity) = true;
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::PlaneSound, 0, -1);
		adversities.at(ecs::AdversityID::PlaneAdversity)->reset();
		playingWarning = false;
		active = false;
		if (!planeQueue.empty()) {
			setTimerTime(ecs::AdversityID::PlaneAdversity, planeQueue.front());
			planeQueue.pop();
		}
	}

	hookTimer->update();

	if (hookTimer->isTimerEnd()) {
		hookTimer->timerReset();
		activeAdversities.at(ecs::AdversityID::HookAdversity) = true;
		adversities.at(ecs::AdversityID::HookAdversity)->reset();
		playingWarning = false;
		active = false;
		if (!hookQueue.empty()) {
			setTimerTime(ecs::AdversityID::HookAdversity, hookQueue.front());
			hookQueue.pop();
		}
	}

	rainTimer->update();

	if (rainTimer->isTimerEnd()) {
		rainTimer->timerReset();
		activeAdversities.at(ecs::AdversityID::RainAdversity) = true;
		adversities.at(ecs::AdversityID::RainAdversity)->reset();
		playingWarning = false;
		active = false;
		if (!rainQueue.empty()) {
			setTimerTime(ecs::AdversityID::RainAdversity, rainQueue.front());
			rainQueue.pop();
		}
	}

	burnCookerTimer->update();

	if (burnCookerTimer->isTimerEnd()) {
		burnCookerTimer->timerReset();
		activeAdversities.at(ecs::AdversityID::CookersAdversity) = true;
		adversities.at(ecs::AdversityID::CookersAdversity)->reset();
		playingWarning = false;
		active = false;
		if (!cookerQueue.empty()) {
			setTimerTime(ecs::AdversityID::CookersAdversity, cookerQueue.front());
			cookerQueue.pop();
		}
	}

}

void MultipleAdversityManager::draw()
{
	for (int i = 0; i < activeAdversities.size(); ++i) {
		if (activeAdversities[i]) adversities[i]->draw();
	}
	if (active) warningTexture->render(RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight()));
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
	activeAdversities[i] = false;
}

void MultipleAdversityManager::setTimerTime(ecs::AdversityID id, int time)
{
	switch (id) {
	case ecs::AdversityID::RainAdversity:
		rainWarning->timerReset();
		rainWarning->setTime(time);
		rainWarning->timerStart();
		rainTimer->timerReset();
		rainTimer->setTime(time + 2000);
		rainTimer->timerStart();
		break;
	case ecs::AdversityID::HookAdversity:
		hookWarning->timerReset();
		hookWarning->setTime(time);
		hookWarning->timerStart();
		hookTimer->timerReset();
		hookTimer->setTime(time + 2000);
		hookTimer->timerStart();
		break;
	case ecs::AdversityID::PlaneAdversity:
		planeWarning->timerReset();
		planeWarning->setTime(time);
		planeWarning->timerStart();
		planeTimer->timerReset();
		planeTimer->setTime(time + 2000);
		planeTimer->timerStart();
		break;
	case ecs::AdversityID::CookersAdversity:
		burnCookerTimer->timerReset();
		burnedCookerWarning->setTime(time);
		burnedCookerWarning->timerStart();
		burnCookerTimer->timerReset();
		burnCookerTimer->setTime(time + 2000);
		burnCookerTimer->timerStart();
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
