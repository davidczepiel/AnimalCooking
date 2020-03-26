#include "OrderManager.h"
#include "FoodDictionary.h"

OrderManager::OrderManager() : OrderManager(2, 100, {100, 700})
{
}

OrderManager::OrderManager(size_t maxOrders, size_t deltaPosXBetweenOrder, Vector2D position) : Component(ecs::OrderManager),
		currentOrders_(maxOrders, nullptr), //Inicializa los vectores con su size a sus valores por defecto
		distXBetweenOrders_(deltaPosXBetweenOrder), position_(position)
{
}

OrderManager::~OrderManager()
{
	for (auto o : currentOrders_) {
		delete o;
	}
}

//void OrderManager::update()
//{
//	for (auto o : currentOrders_) {
//		if (o != nullptr) o->update();
//	}
//}

void OrderManager::setMaxOrders(size_t size)
{
	currentOrders_.resize(size, nullptr);
}

void OrderManager::addOrder(Resources::FoodType finalProduct)
{
	vector<Order*>::iterator it = getFreePos();
	if (it != currentOrders_.end()) { //Si hay hueco se mete el pedido, y si no hay, el cliente se va

		set<int> ings_ = FoodDictionary::instance()->getIngsForFood(finalProduct); //Recibe los ingredientes que usa ese pedido

		if (!ings_.empty()) {

			//Vector de texturas
			vector<Texture*> texturesIngs_;
			for (auto i : ings_) {				//el id de Resources::FoodType debe coincidir con el de Resources::Textures
				texturesIngs_.push_back(game_->getTextureMngr()->getTexture(i)); 
			}

			//Mete el pedido
			*it = new Order( //Mete un order en la posicion libre			 

				//Se asigna la posicion a los orders aqui, pero tal vez deberia ser el OrderViewer

				Vector2D(position_.getX() + distXBetweenOrders_ * (it - currentOrders_.begin()), position_.getY()), // pos en x es relativa a su posicion en el vector
				game_->getTextureMngr()->getTexture(finalProduct), // OrderText
				texturesIngs_, // ingsText
				finalProduct
			);
		}
	}
}

void OrderManager::removeOrder(Resources::FoodType finalProduct, bool playerDidIt)
{
	vector<Order*>::iterator it = getIndexOf(finalProduct);
	if (it != currentOrders_.end()) { //Si encuentra el producto a eliminar, elimina el pedido
		delete *it; 	
		*it = nullptr;

		if (playerDidIt);// Anadir puntos al ScoreManager
	}
}

vector<Order*>& OrderManager::getOrders()
{
	return currentOrders_;
}

vector<Order*>::iterator OrderManager::getFreePos()
{
	vector<Order*>::iterator it = currentOrders_.begin();
	while (it != currentOrders_.end()) {
		if (*it == nullptr) break; //Paro la busqueda cuando encuentro una posicion libre
		++it;
	}
	return it;
}

vector<Order*>::iterator OrderManager::getIndexOf(Resources::FoodType finalProduct)
{
	vector<Order*>::iterator it = currentOrders_.begin();
	while (it != currentOrders_.end()) {
		if ((*it)->getFinalProduct()) == finalProduct) break; //Paro la busqueda cuando encuentro el pedido de finalProduct
		++it;
	}
	return it;
}
