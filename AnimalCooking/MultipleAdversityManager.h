#pragma once
#include "Component.h"
#include "Timer.h"
#include "Adversity.h"
#include "Transform.h"
#include "CookerPool.h"
#include "UtensilsPool.h"
#include "IngredientsPool.h"

#include <queue>
#include <tuple>

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
	AdversityTimer* rainTimer;
	AdversityTimer* rainWarning;
	AdversityTimer* planeTimer;
	AdversityTimer* planeWarning;
	AdversityTimer* hookTimer;
	AdversityTimer* hookWarning;
	AdversityTimer* burnCookerTimer;
	AdversityTimer* burnedCookerWarning;
	AdversityTimer* adversityTimer;
	bool playingWarning, active;
	int warningRate;

	queue<int> planeQueue;
	queue<int> rainQueue;
	queue<int> cookerQueue;
	queue<int> hookQueue;
	bool justStarted;

	void seeTimers();
	void seeAdversityWarning();

public:
	MultipleAdversityManager(Transform* tp1, Transform* tp2, CookerPool* cp, IngredientsPool* ip, UtensilsPool* up);
	void update();
	void draw();
	void startAdvesities();
	void playAdversity(ecs::AdversityID i) { activeAdversities[i] = true; }
	void stopAdversity(ecs::AdversityID i);
	void setTimerTime(ecs::AdversityID id, int time);

	void addAdversityToQueue(ecs::AdversityID type, int time);

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

