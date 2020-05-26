#include "BurnedCookerAdversity.h"
#include "Cooker.h"
#include "TimerViewer.h"

void BurnedCookerAdversity::StartAdversity() {
	if (!alreadyInitialized) {
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(internalTimer);
		alreadyInitialized = true;
	}
	internalTimer->timerReset();
	internalTimer->setTime(5000);
	internalTimer->timerStart();

	int rnd = SDLGame::instance()->getRandGen()->nextInt(0,cookerPool->getPool().size());
	int i = (rnd + 1) % cookerPool->getPool().size();

	while (i != rnd) {
		if (cookerPool->getPool()[rnd]->getCookerState() == CookerStates::empty) {	//Se elige un cooker que no tenga nada dentro para quemarlo
			targetCooker = cookerPool->getPool()[rnd];
			targetCooker->setCookerState(CookerStates::overheated);
			break;
		}
		else i = (i + 1) % cookerPool->getPool().size();
	}

	if (targetCooker == nullptr) {
		multipleAdversityMngr_->stopAdversity(ecs::AdversityID::CookersAdversity);
	}
}

void BurnedCookerAdversity::update() {
	internalTimer->update();
	if (internalTimer->isTimerEnd() && targetCooker != nullptr) {
		targetCooker->setCookerState(CookerStates::empty);
		targetCooker = nullptr;
		multipleAdversityMngr_->stopAdversity(ecs::AdversityID::CookersAdversity);
	}
}

void BurnedCookerAdversity::draw() {

}

void BurnedCookerAdversity::reset() {
	StartAdversity();
}