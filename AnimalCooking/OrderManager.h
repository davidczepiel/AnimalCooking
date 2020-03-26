#pragma once
#include "Order.h"
#include "Component.h"

class OrderManager : public Component {

public:
	OrderManager();

	//deltaPosXBetweenOrder es el hueco a dejar entre pedido y pedido
	//position es la posicion del primer pedido
	OrderManager(size_t maxOrders, size_t deltaPosXBetweenOrder, Vector2D position);

	~OrderManager();

	//void update() override;

	//Solo llamar cuando aun no se haya hecho ningun pedido
	void setMaxOrders(size_t size);

	void setDistXBetweenOrders(size_t delta) { distXBetweenOrders_ = delta; }

	void setPosition(Vector2D pos) { position_ = pos; }

	//Mete un pedido lo mas a la izquierda posible
	void addOrder(Resources::FoodType finalProduct);

	//Preguntar si el finalProduct se encuentra en el Order o hay que guardalo
	//playerDidIt indica si el jugador a conseguido el pedido o no
	void removeOrder(Resources::FoodType finalProduct, bool playerDidIt);

	//PUEDE DEVOLVER VALORES A NULLPTR
	vector<Order*>& getOrders();

private:
	size_t distXBetweenOrders_;
	Vector2D position_;

	vector<Order*>::iterator getFreePos();
	vector<Order*>::iterator getIndexOf(Resources::FoodType finalProduct);

	vector<Order*> currentOrders_; //Vector para guardar los Order
};