#pragma once
#include "Component.h"
#include <vector>
#include "Resources.h"
#include <queue>
#include <list>
#include "TimerViewer.h"

class OrderManager;

class AIClient : public Component {
public:
	AIClient();
	AIClient(Uint32 deltaTimePerOrder, Uint32 deltaTimeFirstOrder,TimerViewer* tv);

	void init() override;
	void update() override;

	inline void setAvailableOrders(vector<Resources::FoodType>& lista) {
		allOrders_ = lista.empty();
		availableOrders_.insert(availableOrders_.end(), lista.begin(), lista.end());
	}

	inline void setInitialOrders(vector<Resources::FoodType>& lista) {	
		for (auto elem : lista) {
			initialOrders_.push(elem);
		}
	}

	inline void changeOrderGroup(const std::pair<int, int>& g) { group = g; }

private:
	void checkNewOrder();
	Resources::FoodType chooseRandomOrder();

	OrderManager* orMngr_;
	Timer* t;

	queue<Resources::FoodType> initialOrders_;
	vector<Resources::FoodType> availableOrders_; // posibles platos en este nivel

	std::pair<int, int> group;

	Uint32 deltaTimePerOrder_;
	bool firstOrder_;
	bool allOrders_;
};
