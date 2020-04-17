#pragma once
#include "Order.h"
#include "Component.h"
#include "ScoreManager.h"
#include <set>
#include <list>

class OrderManager : public Component {

public:
	OrderManager();

	//deltaPosXBetweenOrder es el hueco a dejar entre pedido y pedido
	//position es la posicion del primer pedido
	OrderManager(size_t maxOrders, size_t deltaPosXBetweenOrder, Vector2D position, ScoreManager* scoreManager);

	~OrderManager();

	inline void setScoreManager(ScoreManager* scoreManager) { scoreManager_ = scoreManager; }

	//void update() override;

	//Solo llamar cuando aun no se haya hecho ningun pedido
	void setMaxOrders(size_t size);

	inline void setDistXBetweenOrders(size_t delta) { distXBetweenOrders_ = delta; }

	inline void setPosition(Vector2D pos) { position_ = pos; }

	//Mete un pedido lo mas a la izquierda posible
	void addOrder(Resources::FoodType finalProduct);

	//playerDidIt indica si el jugador a conseguido el pedido o no para añadir puntos al scoreManager
	//Los puntos que se añaden = numIngs del Order * 15
	bool removeOrder(Resources::FoodType finalProduct, bool playerDidIt);

	//PUEDE DEVOLVER VALORES A NULLPTR
	vector<Order*>& getOrders();

	void fillPosibleOrders(initializer_list<Resources::FoodType>& lista) {
		for (auto elem : lista) {
			availableOrders_.insert(elem);
		}
	}

	inline const set<Resources::FoodType>& getPosibleOrders() const { return availableOrders_; }

private:
	size_t distXBetweenOrders_;
	Vector2D position_;

	ScoreManager* scoreManager_;

	vector<Order*>::iterator getFreePos();
	list<vector<Order*>::iterator>& getListOf(Resources::FoodType finalProduct);
	vector<Order*>::iterator getFirst(const list<vector<Order*>::iterator>& lista);

	set<Resources::FoodType> availableOrders_; // posibles platos en este nivel
	vector<Order*> currentOrders_; //Vector para guardar los Order
};