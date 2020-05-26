#pragma once
#include "Component.h"
#include <vector>
#include "Resources.h"
#include <queue>
#include "TimerViewer.h"

class OrderManager;

class AIClient : public Component {
public:
	AIClient();
	AIClient(Uint32 deltaTimePerOrder, Uint32 deltaTimeFirstOrder,TimerViewer* tv);

	inline void setAvailableOrders(vector<Resources::FoodType>& lista) {
		availableOrders_.insert(availableOrders_.end(), lista.begin(), lista.end());
	}

	inline void setInitialOrders(vector<Resources::FoodType>& lista) {
		for (auto elem : lista) {
			initialOrders_.push(elem);
		}
	}

	void init() override;
	void update() override;
private:
	OrderManager* orMngr_;
	Timer* t;

	queue<Resources::FoodType> initialOrders_;
	vector<Resources::FoodType> availableOrders_; // posibles platos en este nivel

	Uint32 deltaTimePerOrder_;
	bool firstOrder_;

	void checkNewOrder();
	Resources::FoodType chooseRandomOrder();
};
