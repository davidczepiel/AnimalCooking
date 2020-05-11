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
	Texture* warningTexture;
	vector<Adversity*> adversities;
	vector<bool> activeAdversities;
	Transform* tP1;
	Transform* tP2;
	CookerPool* cookerPool;
	IngredientsPool* ingredientsPool;
	UtensilsPool* utensilsPool;
	bool playingAdversity;
	Timer rainTimer, rainWarning;
	Timer planeTimer, planeWarning;
	Timer hookTimer, hookWarning;
	Timer burnCookerTimer, burnedCookerWarning;
	Timer adversityTimer;
	bool playingWarning, active;
	int warningRate;

	void seeTimers();
	void seeAdversityWarning();

public:
	MultipleAdversityManager(Transform* tp1, Transform* tp2, CookerPool* cp, IngredientsPool* ip, UtensilsPool* up);
	void update();
	void draw();
	void playAdversity(ecs::AdversityID i) { activeAdversities[i] = true; }
	void stopAdversity(ecs::AdversityID i);
	void setTimerTime(ecs::AdversityID id, int time);

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
