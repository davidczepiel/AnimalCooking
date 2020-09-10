#pragma once
#include "Component.h"
#include "Timer.h"
#include "Adversity.h"
#include "Transform.h"
#include "CookerPool.h"
#include "UtensilsPool.h"
#include "IngredientsPool.h"
#include "FirePool.h"

#include <queue>
#include <tuple>
#include "GhostPool.h"

class MultipleAdversityManager : public Component
{
public:
	MultipleAdversityManager(Transform* tp1, Transform* tp2, CookerPool* cp, IngredientsPool* ip, UtensilsPool* up, FirePool* fp, GhostPool* gP);
	~MultipleAdversityManager() {
		if (haptic1 != NULL) SDL_HapticClose(haptic1);
		if (haptic2 != NULL) SDL_HapticClose(haptic2);
	}
	void update();
	void draw();
	void startAdvesities();
	void playAdversity(ecs::AdversityID i) { activeAdversities_[i] = true; }
	void stopAdversity(ecs::AdversityID i);

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

	FirePool* getFirePool() {
		return firePool_;
	}

	GhostPool* getGhostPool() {
		return ghostPool_;
	}

private:
	void seeTimers();
	void seeAdversityWarning();
	void playRumbles();

	Texture* warningTexture_;
	Transform* tP1_;
	Transform* tP2_;
	CookerPool* cookerPool_;
	IngredientsPool* ingredientsPool_;
	UtensilsPool* utensilsPool_;
	FirePool* firePool_;
	GhostPool* ghostPool_;
	AdversityTimer* adversityTimer_;

	int warningRate_;
	bool playingWarning_;
	bool active_;
	bool playingAdversity_;
	bool justStarted_;
	bool finishedAdversities;

	vector<Adversity*> adversities_;
	vector<bool> activeAdversities_;
	queue<tuple<int, ecs::AdversityID>> adversitiesQueue_;
	AdversityTimer* nextAdversityTimer_;
	AdversityTimer* nextWarningTimer_;

	Uint32 startRumbleTime_, rumbleCadence_, lengthOfRumble_;
	SDL_Haptic* haptic1 = nullptr, * haptic2 = nullptr;
};

