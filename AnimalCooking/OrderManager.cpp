#include "OrderManager.h"
#include "FoodDictionary.h"
#include "GameConfig.h"
OrderManager::OrderManager() : OrderManager(2, 100, { 100, 700 })
{
}

OrderManager::OrderManager(size_t maxOrders, size_t deltaPosXBetweenOrder, Vector2D position, ScoreManager* scoreManager) : Component(ecs::OrderManager),
currentOrders_(maxOrders, nullptr), //Inicializa los vectores con su size a sus valores por defecto
distXBetweenOrders_(deltaPosXBetweenOrder), position_(position), scoreManager_(scoreManager), msPerIng_(), availableOrders_(), allOrders_()
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
	if (availableOrders_.find(finalProduct) != availableOrders_.end() || allOrders_) { //Si es posible meter este pedido
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
					getTimePerOrder(finalProduct, ings_.size()) //Tiempo que se mantiene en vigor 
				);
				SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::OrderRecieved, 0);
			}
		} 
	}
}

bool OrderManager::removeOrder(Resources::FoodType finalProduct, bool playerDidIt)
{
	list<vector<Order*>::iterator> lista = getListOf(finalProduct);
	if (!lista.empty()) { //Si encuentra el producto a eliminar, elimina el pedido
		vector<Order*>::iterator it = getFirst(lista);

		scoreManager_->setMaxScore(scoreManager_->getMaxScore() + (*it)->getNumIngs() * config::SCORE_MANAGER_SERVED_BONUS);

		if (playerDidIt) {
			if ((*it)->getFinalProduct() == Resources::FoodType::FishAndChips)
				scoreManager_->addScore(3 * config::SCORE_MANAGER_SERVED_BONUS);

			if ((*it)->getFinalProduct() == Resources::FoodType::IcedCookedFish)
				scoreManager_->addScore(5 * config::SCORE_MANAGER_SERVED_BONUS);
			else if((*it)->getFinalProduct() == Resources::FoodType::IcedFishAndChips)
				scoreManager_->addScore(4 * config::SCORE_MANAGER_SERVED_BONUS);
			else if ((*it)->getFinalProduct() == Resources::FoodType::IcedFishBurger)
				scoreManager_->addScore(5 * config::SCORE_MANAGER_SERVED_BONUS);
			else if ((*it)->getFinalProduct() == Resources::FoodType::IcedFishOnStick)
				scoreManager_->addScore(3 * config::SCORE_MANAGER_SERVED_BONUS);
			else if ((*it)->getFinalProduct() == Resources::FoodType::IcedRice1)
				scoreManager_->addScore(3 * config::SCORE_MANAGER_SERVED_BONUS);
			else if ((*it)->getFinalProduct() == Resources::FoodType::IcedRice2)
				scoreManager_->addScore(4 * config::SCORE_MANAGER_SERVED_BONUS);
			else if ((*it)->getFinalProduct() == Resources::FoodType::IcedRiceAndClams)
				scoreManager_->addScore(5 * config::SCORE_MANAGER_SERVED_BONUS);
			else if ((*it)->getFinalProduct() == Resources::FoodType::IcedRiceDish)
				scoreManager_->addScore(5 * config::SCORE_MANAGER_SERVED_BONUS);
			else if ((*it)->getFinalProduct() == Resources::FoodType::Teriyaki2)
				scoreManager_->addScore(5 * config::SCORE_MANAGER_SERVED_BONUS);
			else if ((*it)->getFinalProduct() == Resources::FoodType::Teriyaki3)
				scoreManager_->addScore(6 * config::SCORE_MANAGER_SERVED_BONUS);
			else if ((*it)->getFinalProduct() == Resources::FoodType::Perrito3)
				scoreManager_->addScore(4 * config::SCORE_MANAGER_SERVED_BONUS);
			else
			scoreManager_->addScore((*it)->getNumIngs() * config::SCORE_MANAGER_SERVED_BONUS);
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::IngredientSpawned, 0);
		}
		//else if (scoreManager_->getScore() + (*it)->getNumIngs() * config::SCORE_MANAGER_NOT_SERVED_PENALIZATION >= 0)
		//	scoreManager_->addScore((*it)->getNumIngs() * -1.5);

		(*it)->removeTimer();
		delete* it;
		*it = nullptr;
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::IngredientSpawned, 0);
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

double OrderManager::getTimePerOrder(Resources::FoodType finalProduct, int size)
{
	double time = msPerIng_ * size;	//Tiempo por ingrediente* num ingredientes (cfg)
	double timeCooking = 20.0;		//Tiempo que tarda en cocinar un ingrediente del pedido 
	double iceDelay = 1000;

	switch (finalProduct)
	{
	case Resources::FoodType::Burger: time += timeCooking;
	/*case Resources::FoodType::Burger1: time += 2*timeCooking + 5;*/
	case Resources::FoodType::Burger2: time += timeCooking + 5;
	case Resources::FoodType::Burger3: time += timeCooking + 5;
	case Resources::FoodType::Burger4: time += timeCooking + 5;
	case Resources::FoodType::Burger5: time += timeCooking + 5;
	case Resources::FoodType::RiceDish: time += timeCooking;
	case Resources::FoodType::Risotto: time += timeCooking;

	case Resources::FoodType::Roast: time += timeCooking;
	case Resources::FoodType::Roast1: time += timeCooking;
	case Resources::FoodType::Roast2: time += timeCooking;
	case Resources::FoodType::Roast3: time += timeCooking;

	case Resources::FoodType::CookedFish: time += timeCooking;
	case Resources::FoodType::FishAndChips: time += 3*timeCooking+10;
	case Resources::FoodType::FishOnStick: time += timeCooking+5;
	case Resources::FoodType::FishBurger: time += timeCooking -1000;
	case Resources::FoodType::IcedCookedFish: time += timeCooking + iceDelay;
	case Resources::FoodType::IcedFishOnStick: time += timeCooking + iceDelay+5000;
	case Resources::FoodType::IcedFishAndChips: time += 3*timeCooking + iceDelay+10;
	case Resources::FoodType::IcedFishBurger: time += timeCooking + iceDelay -1000;

	case Resources::FoodType::Rice1: time += timeCooking;
	case Resources::FoodType::Rice2: time += timeCooking;
	case Resources::FoodType::IcedRice1: time += timeCooking + iceDelay;
	case Resources::FoodType::IcedRice2: time += timeCooking + iceDelay;

	case Resources::FoodType::FriedVegs: time += timeCooking;
	case Resources::FoodType::FriedVegs1: time += timeCooking + 5;
	case Resources::FoodType::FriedVegs2: time += timeCooking + 5;
	case Resources::FoodType::BakedChicken: time += timeCooking;
	case Resources::FoodType::BakedChicken1: time += timeCooking;
	case Resources::FoodType::BakedChicken2: time += timeCooking;
	case Resources::FoodType::FrenchFries: time += timeCooking;
	case Resources::FoodType::CookedClams: time += timeCooking;
	case Resources::FoodType::RiceAndClams: time += timeCooking;
	case Resources::FoodType::IcedRiceAndClams: time += timeCooking + iceDelay;
	case Resources::FoodType::IcedRiceDish: time += timeCooking + iceDelay;
	case Resources::FoodType::Teriyaki1: time += 2 * timeCooking+1000;
	case Resources::FoodType::Teriyaki2: time += 2*timeCooking;
	case Resources::FoodType::Teriyaki3: time += 3 * timeCooking + 25000;
	case Resources::FoodType::Pizza: time += timeCooking;
	case Resources::FoodType::Pizza1: time +=  timeCooking;
	case Resources::FoodType::Pizza2: time += timeCooking;
	case Resources::FoodType::Pizza3: time += timeCooking;
	case Resources::FoodType::Pizza4: time += timeCooking +2000;
	case Resources::FoodType::Pizza5: time += timeCooking;
	case Resources::FoodType::Perrito: time += timeCooking;
	case Resources::FoodType::Perrito1: time += timeCooking+1000;
	case Resources::FoodType::Perrito2: time += timeCooking+2000;
	case Resources::FoodType::Perrito3: time += 2*timeCooking+1000;

	default:
		break;
	}
	return time;
}

bool OrderManager::someOneWantsThis(Resources::FoodType finalProduct) {

	list<vector<Order*>::iterator> lista = getListOf(finalProduct);
	if (!lista.empty())
		return true;
	else
		return false;
}
