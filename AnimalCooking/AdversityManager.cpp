#include "AdversityManager.h"

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
		//MyAdversity = new ...;
	}
}
