#include "BurnedCookerAdversity.h"
#include "Cooker.h"

void BurnedCookerAdversity::StartAdversity() {
	internalTimer.timerReset();
	internalTimer.setTime(5000);
	internalTimer.timerStart();

	int rnd = SDLGame::instance()->getRandGen()->nextInt(0,cookerPool->getPool().size());
	int i = rnd + 1 % cookerPool->getPool().size();

	while (i != rnd) {
		if (cookerPool->getPool()[rnd]->getCookerState() == CookerStates::empty) {	//Se elige un cooker que no tenga nada dentro para quemarlo
			targetCooker = cookerPool->getPool()[rnd];
			targetCooker->setCookerState(CookerStates::overheated);
			break;
		}
		else i = (i + 1) % cookerPool->getPool().size();
	}
}

void BurnedCookerAdversity::update() {
	if (internalTimer.isTimerEnd() && targetCooker != nullptr) {
		targetCooker->setCookerState(CookerStates::empty);
		targetCooker = nullptr;
	}
	else internalTimer.update();
}

void BurnedCookerAdversity::draw() {

}

void BurnedCookerAdversity::reset() {
	StartAdversity();
}