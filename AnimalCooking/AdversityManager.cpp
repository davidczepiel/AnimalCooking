#include "AdversityManager.h"
#include "BurnedCookerAdversity.h"
#include "PlaneAdversity.h"
#include "HookAdversity.h"
#include "RainAdversity.h"

void AdversityManager::update()
{
	if (myAdversity != nullptr && playingAdversity)
		myAdversity->update();
}

void AdversityManager::draw()
{
	if (myAdversity != nullptr && playingAdversity)
		myAdversity->draw();
}

void AdversityManager::stopAdversity()
{
	playingAdversity = false;
	myAdversity->reset();
	
}

void AdversityManager::loadAdversity(ecs::AdversityID type)
{
	switch (type) {
		case ecs::AdversityID::CookersAdversity:
			myAdversity = new BurnedCookerAdversity(this, nullptr);
		break;
		case ecs::AdversityID::HookAdversity:
			myAdversity = new HookAdversity(this, nullptr);
		break;
		case ecs::AdversityID::PlaneAdversity:
			myAdversity = new PlaneAdversity(this, nullptr);
			//myAdversity = new BurnedCookerAdversity(this);
		break;
		case ecs::AdversityID::RainAdversity:
			//myAdversity = new RainAdversity(this);
		break;
	}
}
