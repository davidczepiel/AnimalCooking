#include "OrderAdder.h"
#include "OrderService.h"
#include "OrderService.h"
#include "OrderManager.h"
#include "AIClient.h"
#include "Vector2D.h"

#define CASTID(t) static_cast<ecs::GroupID>(t - 1)
#define ADDPEDIDO(p, t) p.push_back(t)

OrderAdder::OrderAdder(EntityManager* em, jute::jValue nivel, jute::jValue general, std::array<Entity*, 2>& player, Entity* gameManager, const double casilla)
{
	OrderService* os = new OrderService({ nivel["Clients"]["repisa"]["pos"]["x"].as_double() * casilla, nivel["Clients"]["repisa"]["pos"]["y"].as_double() * casilla },
		GETCMP2(player[0], Transport), GETCMP2(player[1], Transport), em);

	os->setSize({ general["Clients"]["repisa"]["size"]["width"].as_double() * casilla, general["Clients"]["repisa"]["size"]["height"].as_double() * casilla });
	os->addComponent<OrderServiceViewer>(os);

	OrderManager* om = os->setOrderMngr(os->addComponent<OrderManager>(nivel["Clients"]["pedidos"]["maxPedidos"].as_int(),
		(int)(general["Clients"]["pedidos"]["deltaX"].as_double() * casilla),
		Vector2D(nivel["Clients"]["pedidos"]["pos"]["x"].as_double() * casilla, nivel["Clients"]["pedidos"]["pos"]["y"].as_double() * casilla), GETCMP2(gameManager, ScoreManager)));
	om->setSecondsPerIng(nivel["Clients"]["pedidos"]["segundosPorIngrediente"].as_int());

	os->addComponent<OrderViewer>(general["Clients"]["pedidos"]["size"]["width"].as_double() * casilla, general["Clients"]["pedidos"]["size"]["height"].as_double() * casilla, 
		Vector2D(general["Clients"]["pedidos"]["margin"]["x"].as_double() * casilla, general["Clients"]["pedidos"]["margin"]["y"].as_double() * casilla));
	
	AIClient* ai = os->addComponent<AIClient>(nivel["Clients"]["pedidos"]["segundosEntrePedido"].as_int());

	//Inicializacion de los posibles pedidos en ese nivel
	vector<Resources::FoodType> posibles;
	for (int c = 0; c < nivel["Clients"]["pedidos"]["posiblesPedidos"].size(); ++c) {
		switchPedido(nivel["Clients"]["pedidos"]["posiblesPedidos"][c].as_string(), posibles);
	}
	ai->setAvailableOrders(posibles);
	om->fillPosibleOrders(posibles);

	//Inicializacion de los pedidos iniciales en ese nivel
	vector<Resources::FoodType> iniciales;
	for (int c = 0; c < nivel["Clients"]["pedidos"]["pedidosIniciales"].size(); ++c) {
		switchPedido(nivel["Clients"]["pedidos"]["pedidosIniciales"][c].as_string(), posibles);
	}
	ai->setInitialOrders(iniciales);

	//Inicializacion de los componentes extra de ese nivel
	for (int c = 0; c < nivel["Clients"]["components"].size(); ++c) {
		initializeComponent(nivel["Clients"]["components"][c].as_string(), os);
	}

	em->addEntity(os);
	em->addToGroup(os, CASTID(general["Clients"]["Layer"].as_int()));
	interactives_.push_back(os);
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

void OrderAdder::switchPedido(const string& p, vector<Resources::FoodType>& pedido)
{		
	switch (str2int(p.c_str()))
	{
	case str2int("Salad"):
		ADDPEDIDO(pedido, Resources::FoodType::Salad);
		break;
	case str2int("Burger"):
		ADDPEDIDO(pedido, Resources::FoodType::Burger);
		break;
	case str2int("Pizza"):
		ADDPEDIDO(pedido, Resources::FoodType::Pizza);
		break;
	case str2int("RiceDish"):
		ADDPEDIDO(pedido, Resources::FoodType::RiceDish);
		break;
	case str2int("HotDog"):
		ADDPEDIDO(pedido, Resources::FoodType::HotDog);
		break;
	case str2int("Risotto"):
		ADDPEDIDO(pedido, Resources::FoodType::Risotto);
		break;
	case str2int("CookedFish"):
		ADDPEDIDO(pedido, Resources::FoodType::CookedFish);
		break;
	case str2int("FriedVegs"):
		ADDPEDIDO(pedido, Resources::FoodType::FriedVegs);
		break;
	case str2int("BakedChicken"):
		ADDPEDIDO(pedido, Resources::FoodType::BakedChicken);
		break;
	case str2int("FrenchFries"):
		ADDPEDIDO(pedido, Resources::FoodType::FrenchFries);
		break;
	case str2int("CookedClams"):
		ADDPEDIDO(pedido, Resources::FoodType::CookedClams);
		break;
	case str2int("RiceAndClams"):
		ADDPEDIDO(pedido, Resources::FoodType::RiceAndClams);
		break;
	default:
		break;
	}
}

void OrderAdder::initializeComponent(const string& component, Entity* entity)
{
	switch (str2int(component.c_str()))
	{
	case str2int("AdvEffect"):
		break;
	default:
		break;
	}
}
