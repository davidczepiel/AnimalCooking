#include "OrderAdder.h"
#include "OrderService.h"
#include "OrderService.h"
#include "OrderManager.h"
#include "AIClient.h"
#include "Vector2D.h"
#include "SelectorPopUpEntity.h"
#include "Selector.h"
#include "InteractionRect.h"
#include "TimerViewer.h"
#include "DishPool.h"
#include "OrderAIChanger.h"

#define CASTID(t) static_cast<ecs::GroupID>(t - 1)
#define ADDPEDIDO(p, t) p.push_back(t)

OrderAdder::OrderAdder(EntityManager* em, jute::jValue& nivel, jute::jValue& general,
	std::array<Entity*, 2>& player, Entity* gameManager, const double casillaX, const double casillaY, TimerViewer* tv, DishPool* dp)
{
	OrderService* os = new OrderService(GETCMP2(player[0], Transport), GETCMP2(player[1], Transport), em, dp);

	tv_ = tv;

	em->addEntity(os);
	em->addToGroup(os, CASTID(general["Clients"]["Layer"].as_int()));
	interactives_.push_back(os);

	os->addComponent<SelectorPopUpEntity>(GETCMP2(player[0], InteractionRect), GETCMP2(player[1], InteractionRect),
		GETCMP2(player[0], Selector), GETCMP2(player[1], Selector), os);

	os->setPos(Vector2D(nivel["Clients"]["repisa"]["pos"]["x"].as_double() * casillaX, nivel["Clients"]["repisa"]["pos"]["y"].as_double() * casillaY));
	os->setSize(Vector2D(general["Clients"]["repisa"]["size"]["width"].as_double() * casillaX, general["Clients"]["repisa"]["size"]["height"].as_double() * casillaY));

	os->setHitboxOffset(Vector2D(0, os->getSize().getY() * 0.25));
	os->setHitboxSize(Vector2D(os->getSize().getX(), os->getSize().getY() * 0.75));


	os->addComponent<OrderServiceViewer>(os);

	OrderManager* om = os->setOrderMngr(os->addComponent<OrderManager>(nivel["Clients"]["pedidos"]["maxPedidos"].as_int(),
		(int)(general["Clients"]["pedidos"]["deltaX"].as_double() * casillaX),
		Vector2D(nivel["Clients"]["pedidos"]["pos"]["x"].as_double() * casillaX, nivel["Clients"]["pedidos"]["pos"]["y"].as_double() * casillaY), GETCMP2(gameManager, ScoreManager)));
	om->setSecondsPerIng(nivel["Clients"]["pedidos"]["segundosPorIngrediente"].as_double());

	os->addComponent<OrderViewer>(general["Clients"]["pedidos"]["size"]["width"].as_double() * casillaX, general["Clients"]["pedidos"]["size"]["height"].as_double() * casillaY,
		Vector2D(general["Clients"]["pedidos"]["margin"]["x"].as_double() * casillaX, general["Clients"]["pedidos"]["margin"]["y"].as_double() * casillaY));

	AIClient* ai = os->addComponent<AIClient>(nivel["Clients"]["pedidos"]["segundosEntrePedido"].as_double() * 1000, nivel["Clients"]["pedidos"]["segundosPrimerPedido"].as_double() * 1000, tv);

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
		switchPedido(nivel["Clients"]["pedidos"]["pedidosIniciales"][c].as_string(), iniciales);
	}
	ai->setInitialOrders(iniciales);

	//Inicializacion de los componentes extra de ese nivel
	for (int c = 0; c < nivel["Clients"]["components"].size(); ++c) {
		initializeComponent(nivel["Clients"]["components"][c].as_string(), os);
	}
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

void OrderAdder::switchPedido(const string& p, vector<Resources::FoodType>& pedido)
{
	switch (str2int(p.c_str()))
	{
	case str2int("Salad"): 			ADDPEDIDO(pedido, Resources::FoodType::Salad);			break;
	case str2int("Salad1"):			ADDPEDIDO(pedido, Resources::FoodType::Salad1);			break;
	case str2int("Salad2"):			ADDPEDIDO(pedido, Resources::FoodType::Salad2);			break;
	case str2int("Salad3"):			ADDPEDIDO(pedido, Resources::FoodType::Salad3);			break;
	case str2int("Salad4"):			ADDPEDIDO(pedido, Resources::FoodType::Salad4);			break;
	//-----------------------------------------------------------------------------------
	case str2int("Burger"):			ADDPEDIDO(pedido, Resources::FoodType::Burger);			break;
	case str2int("Burger1"):		ADDPEDIDO(pedido, Resources::FoodType::Burger1);		break;
	case str2int("Burger2"):		ADDPEDIDO(pedido, Resources::FoodType::Burger2);		break;
	case str2int("Burger3"):		ADDPEDIDO(pedido, Resources::FoodType::Burger3);		break;
	//-----------------------------------------------------------------------------------
	case str2int("Pizza"):			ADDPEDIDO(pedido, Resources::FoodType::Pizza);			break;
	//-----------------------------------------------------------------------------------
	case str2int("Roast"):			ADDPEDIDO(pedido, Resources::FoodType::Roast);			break;
	case str2int("Roast1"):			ADDPEDIDO(pedido, Resources::FoodType::Roast1);			break;
	case str2int("Roast2"):			ADDPEDIDO(pedido, Resources::FoodType::Roast2);			break;
	case str2int("Roast3"):			ADDPEDIDO(pedido, Resources::FoodType::Roast3);			break;
	//-----------------------------------------------------------------------------------
	case str2int("RiceDish"):		ADDPEDIDO(pedido, Resources::FoodType::RiceDish);		break;
	//-----------------------------------------------------------------------------------
	case str2int("Risotto"):		ADDPEDIDO(pedido, Resources::FoodType::Risotto);		break;
	//-----------------------------------------------------------------------------------
	case str2int("CookedFish"):		ADDPEDIDO(pedido, Resources::FoodType::CookedFish);		break;
	//-----------------------------------------------------------------------------------
	case str2int("FriedVegs"):		ADDPEDIDO(pedido, Resources::FoodType::FriedVegs);		break;
	case str2int("FriedVegs1"):		ADDPEDIDO(pedido, Resources::FoodType::FriedVegs1);		break;
	case str2int("FriedVegs2"):		ADDPEDIDO(pedido, Resources::FoodType::FriedVegs2);		break;
	//-----------------------------------------------------------------------------------
	case str2int("BakedChicken"):	ADDPEDIDO(pedido, Resources::FoodType::BakedChicken);	break;
	case str2int("BakedChicken1"):	ADDPEDIDO(pedido, Resources::FoodType::BakedChicken1);	break;
	case str2int("BakedChicken2"):	ADDPEDIDO(pedido, Resources::FoodType::BakedChicken2);	break;
	//-----------------------------------------------------------------------------------
	case str2int("FrenchFries"):	ADDPEDIDO(pedido, Resources::FoodType::FrenchFries);	break;
	//-----------------------------------------------------------------------------------
	case str2int("CookedClams"):	ADDPEDIDO(pedido, Resources::FoodType::CookedClams);	break;
	//-----------------------------------------------------------------------------------
	case str2int("RiceAndClams"):	ADDPEDIDO(pedido, Resources::FoodType::RiceAndClams);	break;
	//-----------------------------------------------------------------------------------
	case str2int("FishOnStick"):	ADDPEDIDO(pedido, Resources::FoodType::FishOnStick);	break;
	case str2int("FishAndChips"):	ADDPEDIDO(pedido, Resources::FoodType::FishAndChips);	break;
	case str2int("FishBurger"):	ADDPEDIDO(pedido, Resources::FoodType::FishBurger);			break;
	//-----------------------------------------------------------------------------------
	case str2int("Rice1"):	ADDPEDIDO(pedido, Resources::FoodType::Rice1);	break;
	case str2int("Rice2"):	ADDPEDIDO(pedido, Resources::FoodType::Rice2);	break;
	//-----------------------------------------------------------------------------------
	case str2int("IcedCookedFish"):	ADDPEDIDO(pedido, Resources::FoodType::IcedCookedFish);			break;
	case str2int("IcedFishOnStick"):	ADDPEDIDO(pedido, Resources::FoodType::IcedFishOnStick);	break;
	case str2int("IcedFishAndChips"):	ADDPEDIDO(pedido, Resources::FoodType::IcedFishAndChips);	break;
	case str2int("IcedFishBurger"):	ADDPEDIDO(pedido, Resources::FoodType::IcedFishBurger);			break;
	case str2int("IcedRice1"):	ADDPEDIDO(pedido, Resources::FoodType::IcedRice1);					break;
	case str2int("IcedRice2"):	ADDPEDIDO(pedido, Resources::FoodType::IcedRice2);					break;
	//-----------------------------------------------------------------------------------
	case str2int("Sushi1"):	ADDPEDIDO(pedido, Resources::FoodType::Sushi1);					break;
	case str2int("Sushi2"):	ADDPEDIDO(pedido, Resources::FoodType::Sushi2);					break;
	case str2int("Sushi3"):	ADDPEDIDO(pedido, Resources::FoodType::Sushi3);					break;
	case str2int("Sushi4"):	ADDPEDIDO(pedido, Resources::FoodType::Sushi4);					break;
	case str2int("Sushi5"):	ADDPEDIDO(pedido, Resources::FoodType::Sushi5);					break;
	case str2int("Onigiri"):	ADDPEDIDO(pedido, Resources::FoodType::Onigiri);			break;
	case str2int("Teriyaki1"):	ADDPEDIDO(pedido, Resources::FoodType::Teriyaki1);			break;
	case str2int("Teriyaki2"):	ADDPEDIDO(pedido, Resources::FoodType::Teriyaki2);			break;
	case str2int("Teriyaki3"):	ADDPEDIDO(pedido, Resources::FoodType::Teriyaki3);			break;
	case str2int("Teriyaki4"):	ADDPEDIDO(pedido, Resources::FoodType::Teriyaki4);			break;
	//-----------------------------------------------------------------------------------
	case str2int("Pizza1"):	ADDPEDIDO(pedido, Resources::FoodType::Pizza1);					break;
	case str2int("Pizza2"):	ADDPEDIDO(pedido, Resources::FoodType::Pizza2);					break;
	case str2int("Pizza3"):	ADDPEDIDO(pedido, Resources::FoodType::Pizza3);					break;
	case str2int("Pizza4"):	ADDPEDIDO(pedido, Resources::FoodType::Pizza4);					break;
	case str2int("Pizza5"):	ADDPEDIDO(pedido, Resources::FoodType::Pizza5);					break;
	case str2int("Perrito"):	ADDPEDIDO(pedido, Resources::FoodType::Perrito);			break;
	case str2int("Perrito1"):	ADDPEDIDO(pedido, Resources::FoodType::Perrito1);			break;
	case str2int("Perrito2"):	ADDPEDIDO(pedido, Resources::FoodType::Perrito2);			break;
	case str2int("Perrito3"):	ADDPEDIDO(pedido, Resources::FoodType::Perrito3);			break;

	case str2int("All"):		/* Dejar vacio : vacio significa todos */					break;
	//-----------------------------------------------------------------------------------
	default:																				break;
	}
}

void OrderAdder::initializeComponent(const string& component, Entity* entity)
{
	switch (str2int(component.c_str()))
	{
	case str2int("Changer"):
		entity->addComponent<OrderAIChanger>(initializer_list<int>{70, 140, 230, 350}, tv_);
		break;
	default:
		break;
	}
}
