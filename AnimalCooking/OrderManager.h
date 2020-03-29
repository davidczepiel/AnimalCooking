#pragma once
#include "Order.h"
#include "Component.h"
#include "ScoreManager.h"

class OrderManager : public Component {

public:
	OrderManager();

	//deltaPosXBetweenOrder es el hueco a dejar entre pedido y pedido
	//position es la posicion del primer pedido
	OrderManager(size_t maxOrders, size_t deltaPosXBetweenOrder, Vector2D position, ScoreManager* scoreManager);

	~OrderManager();

	void setScoreManager(ScoreManager* scoreManager) { scoreManager_ = scoreManager; }

	//void update() override;

	//Solo llamar cuando aun no se haya hecho ningun pedido
	void setMaxOrders(size_t size);

	void setDistXBetweenOrders(size_t delta) { distXBetweenOrders_ = delta; }

	void setPosition(Vector2D pos) { position_ = pos; }

	//Mete un pedido lo mas a la izquierda posible
	void addOrder(Resources::FoodType finalProduct);

	//playerDidIt indica si el jugador a conseguido el pedido o no para añadir puntos al scoreManager
	//Los puntos que se añaden = numIngs del Order * 15
	void removeOrder(Resources::FoodType finalProduct, bool playerDidIt);

	//PUEDE DEVOLVER VALORES A NULLPTR
	vector<Order*>& getOrders();

private:
	size_t distXBetweenOrders_;
	Vector2D position_;

	ScoreManager* scoreManager_;

	vector<Order*>::iterator getFreePos();
	vector<Order*>::iterator getIndexOf(Resources::FoodType finalProduct);

	vector<Order*> currentOrders_; //Vector para guardar los Order
};