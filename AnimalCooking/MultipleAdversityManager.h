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
public:
	MultipleAdversityManager(Transform* tp1, Transform* tp2, CookerPool* cp, IngredientsPool* ip, UtensilsPool* up);
	~MultipleAdversityManager() {
		if (haptic1 != NULL) SDL_HapticClose(haptic1);
		if (haptic2 != NULL) SDL_HapticClose(haptic2);
	}
	void update();
	void draw();
	void startAdvesities();
	void playAdversity(ecs::AdversityID i) { activeAdversities_[i] = true; }
	void stopAdversity(ecs::AdversityID i);
	void setTimerTime(ecs::AdversityID id, int time);

	void addAdversityToQueue(ecs::AdversityID type, int time);

	Transform* getTransformPlayer(Resources::Player player) {
		return player == Resources::Player1 ? tP1_ : tP2_;
	}

	CookerPool* getCookerPool() {
		return cookerPool_;
	}

	IngredientsPool* getIngredientsPool() {
		return ingredientsPool_;
	}

	UtensilsPool* getUtensilsPool() {
		return utensilsPool_;
	}

private:
	void seeTimers();
	void seeAdversityWarning();
	void playRumbles();

	Texture* warningTexture_;
	vector<Adversity*> adversities_;
	vector<bool> activeAdversities_;
	Transform* tP1_;
	Transform* tP2_;
	CookerPool* cookerPool_;
	IngredientsPool* ingredientsPool_;
	UtensilsPool* utensilsPool_;
	AdversityTimer* rainTimer_;
	AdversityTimer* rainWarning_;
	AdversityTimer* planeTimer_;
	AdversityTimer* planeWarning_;
	AdversityTimer* hookTimer_;
	AdversityTimer* hookWarning_;
	AdversityTimer* burnCookerTimer_;
	AdversityTimer* burnedCookerWarning_;
	AdversityTimer* adversityTimer_;

	queue<int> planeQueue;
	queue<int> rainQueue;
	queue<int> cookerQueue;
	queue<int> hookQueue;

	int warningRate_;
	bool playingWarning_;
	bool active_;
	bool playingAdversity_;
	bool justStarted_;

	Uint32 startRumbleTime_, rumbleCadence_, lengthOfRumble_;
	SDL_Haptic* haptic1 = nullptr, * haptic2 = nullptr;
};

