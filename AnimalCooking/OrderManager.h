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
	OrderManager(size_t maxOrders, size_t deltaPosXBetweenOrder, Vector2D position, ScoreManager* scoreManager = nullptr);

	~OrderManager();
	//PUEDE DEVOLVER VALORES A NULLPTR
	inline const set<Resources::FoodType>& getPosibleOrders() const { return availableOrders_; }
	bool someOneWantsThis(Resources::FoodType finalProduct);
	vector<Order*>& getOrders();

	inline void setScoreManager(ScoreManager* scoreManager) { scoreManager_ = scoreManager; }
	//Solo llamar cuando aun no se haya hecho ningun pedido
	void setMaxOrders(size_t size);
	//void update() override;
	inline void setDistXBetweenOrders(size_t delta) { distXBetweenOrders_ = delta; }
	inline void setPosition(Vector2D pos) { position_ = pos; }
	inline void setSecondsPerIng(double s) { msPerIng_ = s * 1000; }

	//Mete un pedido lo mas a la izquierda posible
	void addOrder(Resources::FoodType finalProduct);
	//playerDidIt indica si el jugador a conseguido el pedido o no para a�adir puntos al scoreManager
	//Los puntos que se a�aden = numIngs del Order * 15
	bool removeOrder(Resources::FoodType finalProduct, bool playerDidIt);
	void fillPosibleOrders(vector<Resources::FoodType>& lista) {
		allOrders_ = lista.empty();
		for (auto elem : lista) {
			availableOrders_.insert(elem);
		}
	}

private:
	bool allOrders_;
	size_t distXBetweenOrders_;
	Vector2D position_;
	ScoreManager* scoreManager_;
	vector<Order*>::iterator getFreePos();
	list<vector<Order*>::iterator> getListOf(Resources::FoodType finalProduct);
	vector<Order*>::iterator getFirst(const list<vector<Order*>::iterator>& lista);
	set<Resources::FoodType> availableOrders_; // posibles platos en este nivel
	vector<Order*> currentOrders_; //Vector para guardar los Order

	double msPerIng_;

	double getTimePerOrder(Resources::FoodType finalProduct, int size);
};