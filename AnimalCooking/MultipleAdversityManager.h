#pragma once
#include "Component.h"
#include "Timer.h"
#include "Adversity.h"
#include "Transform.h"
#include "CookerPool.h"
#include "UtensilsPool.h"
#include "IngredientsPool.h"
class MultipleAdversityManager : public Component
{
	vector<Adversity*> adversities;
	vector<bool> activeAdversities;
	Transform* tP1;
	Transform* tP2;
	CookerPool* cookerPool;
	IngredientsPool* ingredientsPool;
	UtensilsPool* utensilsPool;
	bool playingAdversity;

public:
	MultipleAdversityManager(Transform* tp1, Transform* tp2, CookerPool* cp, IngredientsPool* ip, UtensilsPool* up);
	void update();
	void draw();
	void playAdversity(ecs::AdversityID i) { activeAdversities[i] = true; }
	void stopAdversity(ecs::AdversityID i) { activeAdversities[i] = false; }

	Transform* getTransformPlayer(Resources::Player player) {
		return player == Resources::Player1 ? tP1 : tP2;
	}

	CookerPool* getCookerPool() {
		return cookerPool;
	}

	IngredientsPool* getIngredientsPool() {
		return ingredientsPool;
	}

	UtensilsPool* getUtensilsPool() {
		return utensilsPool;
	}

};

