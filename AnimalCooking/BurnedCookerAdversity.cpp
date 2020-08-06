#include "BurnedCookerAdversity.h"
#include "Cooker.h"
#include "TimerViewer.h"

BurnedCookerAdversity::BurnedCookerAdversity(MultipleAdversityManager* mam) : 
	Adversity(mam), 
	internalTimer_(new Timer()),
	cookerPool_(mam->getCookerPool()), 
	targetCooker_(nullptr), 
	alreadyInitialized_(false) {
}

void BurnedCookerAdversity::StartAdversity() {
	if (!alreadyInitialized_) {
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(internalTimer_);
		alreadyInitialized_ = true;
	}
	internalTimer_->timerReset();
	internalTimer_->setTime(5000);
	internalTimer_->timerStart();

	int rnd = SDLGame::instance()->getRandGen()->nextInt(0,cookerPool_->getPool().size());
	int i = (rnd + 1) % cookerPool_->getPool().size();

	while (i != rnd) {
		if (cookerPool_->getPool()[rnd]->getCookerState() == CookerStates::empty) {	//Se elige un cooker que no tenga nada dentro para quemarlo
			targetCooker_ = cookerPool_->getPool()[rnd];
			targetCooker_->setCookerState(CookerStates::overheated);
			break;
		}
		else i = (i + 1) % cookerPool_->getPool().size();
	}

	if (targetCooker_ == nullptr) {
		multipleAdversityMngr_->stopAdversity(ecs::AdversityID::CookersAdversity);
	}
}

void BurnedCookerAdversity::update() {
	internalTimer_->update();
	if (internalTimer_->isTimerEnd() && targetCooker_ != nullptr) {
		targetCooker_->setCookerState(CookerStates::empty);
		targetCooker_ = nullptr;
		multipleAdversityMngr_->stopAdversity(ecs::AdversityID::CookersAdversity);
	}
}

void BurnedCookerAdversity::draw() {

}

void BurnedCookerAdversity::reset() {
	//StartAdversity();
}

void BurnedCookerAdversity::start()
{
	StartAdversity();
}
