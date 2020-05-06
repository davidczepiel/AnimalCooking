#include "MultipleAdversityManager.h"
#include "BurnedCookerAdversity.h"
#include "PlaneAdversity.h"
#include "HookAdversity.h"
#include "RainAdversity.h"


MultipleAdversityManager::MultipleAdversityManager(Transform* tp1, Transform* tp2, CookerPool* cp, IngredientsPool* ip, UtensilsPool* up) : Component(ecs::AdversityManager), tP1(tp1), tP2(tp2), cookerPool(cp), ingredientsPool(ip), utensilsPool(up)
{
	adversities.push_back(new PlaneAdversity(nullptr, this));
	adversities.push_back(new BurnedCookerAdversity(nullptr, this));
	adversities.push_back(new HookAdversity(nullptr, this));
	adversities.push_back(new RainAdversity(nullptr, this));

	for (int i = 0; i < 4; ++i) activeAdversities.push_back(false);
}

void MultipleAdversityManager::update()
{
	seeTimers();
	for (int i = 0; i < activeAdversities.size(); ++i) {
		if (activeAdversities[i]) adversities[i]->update();
	}
}


void MultipleAdversityManager:: seeTimers() {
	planeTimer.update();
	if (planeTimer.isTimerEnd()) {
		planeTimer.timerReset();
		activeAdversities.at(ecs::AdversityID::PlaneAdversity) = true;
		adversities.at(ecs::AdversityID::PlaneAdversity)->reset();
	}
	hookTimer.update();
	if (hookTimer.isTimerEnd()) {
		hookTimer.timerReset();
		activeAdversities.at(ecs::AdversityID::HookAdversity) = true;
		adversities.at(ecs::AdversityID::HookAdversity)->reset();
	}
	rainTimer.update();
	if (rainTimer.isTimerEnd()) {
		rainTimer.timerReset();
		activeAdversities.at(ecs::AdversityID::RainAdversity) = true;
		adversities.at(ecs::AdversityID::RainAdversity)->reset();
	}
	burnCookerTimer.update();
	if (burnCookerTimer.isTimerEnd()) {
		burnCookerTimer.timerReset();
		activeAdversities.at(ecs::AdversityID::CookersAdversity) = true;
		adversities.at(ecs::AdversityID::CookersAdversity)->reset();
	}
	
}

void MultipleAdversityManager::draw()
{
	for (int i = 0; i < activeAdversities.size(); ++i) {
		if (activeAdversities[i]) adversities[i]->draw();
	}
}

void MultipleAdversityManager::stopAdversity(ecs::AdversityID i)
{
	 activeAdversities[i] = false;
}

void MultipleAdversityManager::setTimerTime(ecs::AdversityID id, int time)
{
	switch (id) {
	case ecs::AdversityID::RainAdversity:
		rainTimer.setTime(time);
		rainTimer.timerStart();
		break;
	case ecs::AdversityID::HookAdversity:
		hookTimer.setTime(time);
		hookTimer.timerStart();
		break;
	case ecs::AdversityID::PlaneAdversity:
		planeTimer.setTime(time);
		planeTimer.timerStart();
		break;
	case ecs::AdversityID::CookersAdversity:
		burnCookerTimer.setTime(time);
		burnCookerTimer.timerStart();
		break;
	}
}
