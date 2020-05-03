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
	for (int i = 0; i < activeAdversities.size(); ++i) {
		if (activeAdversities[i]) adversities[i]->update();
	}
}

void MultipleAdversityManager::draw()
{
	for (int i = 0; i < activeAdversities.size(); ++i) {
		if (activeAdversities[i]) adversities[i]->draw();
	}
}
