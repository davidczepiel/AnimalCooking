#pragma once
#include "Component.h"
#include <vector>
#include "Resources.h"
#include <queue>
class OrderManager;

class AIClient : public Component {
public:
	AIClient();
	AIClient(Uint32 deltaTimePerOrder);

	inline void setDeltaTimePerOrder(Uint32 time) { deltaTimePerOrder_ = time; }

	inline void setAvailableOrders(initializer_list<Resources::FoodType>& lista) {
		availableOrders_.insert(availableOrders_.end(), lista.begin(), lista.end());
	}
	inline void setInitialOrders(initializer_list<Resources::FoodType>& lista) {
		for (auto elem : lista) {
			initialOrders_.push(elem);
		}
	}

	void init() override;
	void update() override;
private:
	OrderManager* orMngr_;
	Uint32 deltaTimePerOrder_;
	Uint32 lastOrderTime_;

	queue<Resources::FoodType> initialOrders_;
	vector<Resources::FoodType> availableOrders_; // posibles platos en este nivel

	void checkNewOrder();
	Resources::FoodType chooseRandomOrder();
};