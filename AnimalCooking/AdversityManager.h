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
	AdversityManager(Transform* tp1, Transform* tp2, CookerPool* cp, IngredientsPool* ip, UtensilsPool* up) :Component(ecs::AdversityManager), tP1(tp1), tP2(tp2), cookerPool(cp), ingredientsPool(ip), utensilsPool(up),playingAdversity(false), myAdversity(nullptr) {}
	void update();
	void draw();
	void playAdversity() 
	{ playingAdversity = true; }
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

