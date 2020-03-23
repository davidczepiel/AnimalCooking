#pragma once
#include "Order.h"
#include "Component.h"

class OrderManager : public Component {

public:
	OrderManager();
	OrderManager(size_t maxOrders);
	~OrderManager();

	//void update() override;

	//Solo llamar cuando aun no se haya hecho ningun pedido
	void setMaxOrders(size_t size);

	//Se asigna la posicion a los orders aqui, pero tal vez deberia ser el OrderViewer
	void setDistXBetweenOrders(size_t delta) { distXBetweenOrders_ = delta; }

	void addOrder(Resources::FoodType finalProduct);

	//Preguntar si el finalProduct se encuentra en el Order o hay que guardalo
	void removeOrder(Resources::FoodType finalProduct);

	//PUEDE DEVOLVER VALORES A NULLPTR
	vector<Order*>& getOrders();

private:
	size_t distXBetweenOrders_;

	vector<Order*>::iterator getFreePos();
	vector<Order*>::iterator getIndexOf(Resources::FoodType finalProduct);

	vector<Resources::FoodType> products_; //Vector para guardar los pedidos, como enum, que tengo
	vector<Order*> currentOrders_; //Vector para guardar los Order
};