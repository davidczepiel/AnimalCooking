#include "OrderManager.h"
#include "FoodDictionary.h"

OrderManager::OrderManager() : OrderManager(2, 100, { 100, 700 })
{
}

OrderManager::OrderManager(size_t maxOrders, size_t deltaPosXBetweenOrder, Vector2D position, ScoreManager* scoreManager) : Component(ecs::OrderManager),
		currentOrders_(maxOrders, nullptr), //Inicializa los vectores con su size a sus valores por defecto
		distXBetweenOrders_(deltaPosXBetweenOrder), position_(position), scoreManager_(scoreManager)
{
}

OrderManager::~OrderManager()
{
	for (auto o : currentOrders_) {
		delete o;
	}
}

void OrderManager::setMaxOrders(size_t size)
{
	currentOrders_.resize(size, nullptr);
}

void OrderManager::addOrder(Resources::FoodType finalProduct)
{
	if (availableOrders_.find(finalProduct) != availableOrders_.end()) { //Si es posible meter este pedido
		vector<Order*>::iterator it = getFreePos();
		if (it != currentOrders_.end()) { //Si hay hueco se mete el pedido, y si no hay, el cliente se va		
			set<int> ings_ = FoodDictionary::instance()->getIngsForFood(finalProduct); //Recibe los ingredientes que usa ese pedido
			if (!ings_.empty()) {
				//Mete el pedido
				*it = new Order( //Mete un order en la posicion libre			 
					Vector2D(position_.getX() + distXBetweenOrders_ * (it - currentOrders_.begin()), position_.getY()), // pos en x es relativa a su posicion en el vector
					game_->getTextureMngr()->getTexture(Resources::Bocadillo - Resources::_FirstOfFoods_ + finalProduct), // OrderText
					ings_.size(), // ingsSize
					finalProduct, //Producto que da
					msPerIng_ * ings_.size() //Tiempo que se mantiene en vigor
				);
			}
		}
	}
}

bool OrderManager::removeOrder(Resources::FoodType finalProduct, bool playerDidIt)
{
	list<vector<Order*>::iterator> lista = getListOf(finalProduct);
	if (!lista.empty()) { //Si encuentra el producto a eliminar, elimina el pedido
		vector<Order*>::iterator it = getFirst(lista);
		if (playerDidIt) scoreManager_->addScore((*it)->getNumIngs() * 15);
		delete* it;
		*it = nullptr;
		return true;
	}
	return false;
}

vector<Order*>& OrderManager::getOrders()
{
	return currentOrders_;
}

vector<Order*>::iterator OrderManager::getFreePos()
{
	return find(currentOrders_.begin(), currentOrders_.end(), nullptr);
}

list<vector<Order*>::iterator> OrderManager::getListOf(Resources::FoodType finalProduct)
{
	list<vector<Order*>::iterator> lista;
	vector<Order*>::iterator it = currentOrders_.begin();
	while (it != currentOrders_.end()) {
		if (*it != nullptr && (*it)->getFinalProduct() == finalProduct) lista.push_back(it);
		++it;
	}
	return lista;
}

vector<Order*>::iterator OrderManager::getFirst(const list<vector<Order*>::iterator>& lista)
{
	vector<Order*>::iterator first = (*lista.begin());
	for (vector<Order*>::iterator it : lista) {
		if (*it != nullptr && (*it)->getAnger() > (*first)->getAnger()) first = it;
	}
	return first;
}
