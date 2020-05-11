#include "MultipleAdversityManager.h"
#include "BurnedCookerAdversity.h"
#include "PlaneAdversity.h"
#include "HookAdversity.h"
#include "RainAdversity.h"


MultipleAdversityManager::MultipleAdversityManager(Transform* tp1, Transform* tp2, CookerPool* cp, IngredientsPool* ip, UtensilsPool* up) : Component(ecs::AdversityManager), tP1(tp1), tP2(tp2), cookerPool(cp), ingredientsPool(ip), utensilsPool(up), active(false), playingWarning(false), warningRate(100)
{
	adversities.push_back(new PlaneAdversity(nullptr, this));
	adversities.push_back(new BurnedCookerAdversity(nullptr, this));
	adversities.push_back(new HookAdversity(nullptr, this));
	adversities.push_back(new RainAdversity(nullptr, this));

	warningTexture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::WarningAdversity);

	for (int i = 0; i < 4; ++i) activeAdversities.push_back(false);
}

void MultipleAdversityManager::update()
{
	seeTimers();
	seeAdversityWarning();

	for (int i = 0; i < activeAdversities.size(); ++i) {
		if (activeAdversities[i]) adversities[i]->update();
	}
}

void MultipleAdversityManager::seeAdversityWarning() {
	planeWarning.update();
	if (planeWarning.isTimerEnd()) {
		planeWarning.timerReset();
		playingWarning = true;
		adversityTimer.timerReset();
		adversityTimer.setTime(warningRate);
		adversityTimer.timerStart();
	}
	hookWarning.update();
	if (hookWarning.isTimerEnd()) {
		hookWarning.timerReset();
		playingWarning = true;
		adversityTimer.timerReset();
		adversityTimer.setTime(warningRate);
		adversityTimer.timerStart();
	}
	rainTimer.update();
	if (rainTimer.isTimerEnd()) {
		rainWarning.timerReset();
		playingWarning = true;
		adversityTimer.timerReset();
		adversityTimer.setTime(warningRate);
		adversityTimer.timerStart();
	}
	burnedCookerWarning.update();
	if (burnedCookerWarning.isTimerEnd()) {
		burnedCookerWarning.timerReset();
		playingWarning = true;
		adversityTimer.timerReset();
		adversityTimer.setTime(warningRate);
		adversityTimer.timerStart();
	}

	if (playingWarning) {
		adversityTimer.update();
		if (adversityTimer.isTimerEnd()) {
			if (active) active = false;
			else active = true;

			adversityTimer.timerReset();
			adversityTimer.setTime(warningRate);
			adversityTimer.timerStart();
		}
	}
}

void MultipleAdversityManager:: seeTimers() {
	planeTimer.update();
	
	if (planeTimer.isTimerEnd()) {
		planeTimer.timerReset();
		activeAdversities.at(ecs::AdversityID::PlaneAdversity) = true;
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::PlaneSound, 0, -1);
		adversities.at(ecs::AdversityID::PlaneAdversity)->reset();
		playingWarning = false;
		active = false;
	}

	hookTimer.update();
	
	if (hookTimer.isTimerEnd()) {
		hookTimer.timerReset();
		activeAdversities.at(ecs::AdversityID::HookAdversity) = true;
		adversities.at(ecs::AdversityID::HookAdversity)->reset();
		playingWarning = false;
		active = false;
	}

	rainTimer.update();
	
	if (rainTimer.isTimerEnd()) {
		rainTimer.timerReset();
		activeAdversities.at(ecs::AdversityID::RainAdversity) = true;
		adversities.at(ecs::AdversityID::RainAdversity)->reset();
		playingWarning = false;
		active = false;
	}

	burnCookerTimer.update();
	
	if (burnCookerTimer.isTimerEnd()) {
		burnCookerTimer.timerReset();
		activeAdversities.at(ecs::AdversityID::CookersAdversity) = true;
		adversities.at(ecs::AdversityID::CookersAdversity)->reset();
		playingWarning = false;
		active = false;
	}
	
}

void MultipleAdversityManager::draw()
{
	for (int i = 0; i < activeAdversities.size(); ++i) {
		if (activeAdversities[i]) adversities[i]->draw();
	}
	if (active) warningTexture->render(RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight()));
}

void MultipleAdversityManager::stopAdversity(ecs::AdversityID i)
{
	 activeAdversities[i] = false;
}

void MultipleAdversityManager::setTimerTime(ecs::AdversityID id, int time)
{
	switch (id) {
	case ecs::AdversityID::RainAdversity:
		rainWarning.setTime(time);
		rainWarning.timerStart();
		rainTimer.setTime(time + 2000);
		rainTimer.timerStart();
		break;
	case ecs::AdversityID::HookAdversity:
		hookWarning.setTime(time);
		hookWarning.timerStart();
		hookTimer.setTime(time + 2000);
		hookTimer.timerStart();
		break;
	case ecs::AdversityID::PlaneAdversity:
		planeWarning.setTime(time);
		planeWarning.timerStart();
		planeTimer.setTime(time + 2000);
		planeTimer.timerStart();
		break;
	case ecs::AdversityID::CookersAdversity:
		burnedCookerWarning.setTime(time);
		burnedCookerWarning.timerStart();
		burnCookerTimer.setTime(time + 2000);
		burnCookerTimer.timerStart();
		break;
	}
}
