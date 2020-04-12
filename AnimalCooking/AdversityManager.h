#pragma once
#include "Component.h"
#include "Timer.h"
#include "Adversity.h"
#include "Transform.h"
#include "CookerPool.h"
#include "UtensilsPool.h"
#include "IngredientsPool.h"
class AdversityManager : public Component
{
	Adversity* myAdversity;
	Transform* tP1;
	Transform* tP2;
	CookerPool* cookerPool;
	IngredientsPool* ingredientsPool;
	UtensilsPool* utensilsPool;
	bool playingAdversity;
	
public:
	AdversityManager() :Component(ecs::AdversityManager) {}
	void update();
	void draw();
	void playAdversity() { playingAdversity = true; }
	void stopAdversity();
	void loadAdversity(ecs::AdversityID type);

	Transform* getTransformPlayer(Resources::Player player) {
		return player == Resources::Player1 ? tP1: tP2;
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

