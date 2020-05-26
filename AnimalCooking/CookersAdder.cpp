#include "CookersAdder.h"
#include "CookerPool.h"

#define ADD(t)makeCooker<t>(type, n)

CookersAdder::CookersAdder(Entity* cookersPool, jute::jValue& jsonnivel, jute::jValue& jsongeneral, std::array<Entity*, 2> players, FoodPool* fp, const double casillaX, const double casillaY) :
	nivel(jsonnivel), general(jsongeneral), players(players), cookersPool(cookersPool), casillaX(casillaX), casillaY(casillaY)
{
	CookerPool* cookerP = cookersPool->addComponent<CookerPool>();
	cookersPool->addComponent<FoodCooker>(fp);
	cookersPool->addComponent<CookerViewer>();
	cookersPool->addComponent<InsertExpel>(GETCMP2(players[0], Transport), GETCMP2(players[1], Transport));
	cookersPool->addComponent<SelectorPopUp>(&reinterpret_cast<vector<Interactive*>&>(cookerP->getPool()), GETCMP2(players[0], InteractionRect), GETCMP2(players[1], InteractionRect),
		GETCMP2(players[0], Selector), GETCMP2(players[1], Selector), GETCMP2(players[0], Transport), GETCMP2(players[1], Transport));


	jute::jValue cookerlist = jsonnivel["CookersPool"];
	for (size_t i = 0; i < cookerlist.size(); i++)
	{
		jute::jValue c = jsonnivel["CookersPool"][i][1];
		for (int j = 0; j < c.size(); ++j) {
			switchCookers(cookerlist[i][0].as_string(), i, j);
		}
	}
}
constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
void CookersAdder::switchCookers(const string& cooker, int type, int n) {
	switch (str2int(cooker.c_str()))
	{
	case str2int("Oven"):
		ADD(Oven);
		break;
	case str2int("Skillet"):
		ADD(Skillet);
		break;
	default:
		break;
	}
}
template<typename T>
void CookersAdder::makeCooker(int type, int n) {
	Vector2D pos(nivel["CookersPool"][type][1][n]["pos"]["x"].as_double() * casillaX,
		nivel["CookersPool"][type][1][n]["pos"]["y"].as_double() * casillaY);

	Vector2D size(general["Cookers"]["size"]["width"].as_double() * casillaX,
		general["Cookers"]["size"]["height"].as_double() * casillaY);

	Cooker* c = new T(pos, size, general["Cookers"]["rotation"].as_int(), nullptr,
		GETCMP2(players[0], Transport), GETCMP2(players[1], Transport), cookersPool);

	c->setHitboxSize(Vector2D(c->getSize().getX(), c->getSize().getY()));

	jute::jValue com = nivel["CookersPool"][type][1][n]["components"];
	for (size_t i = 0; i < com.size(); i++)
	{
		initializeComponent(com[i].as_string(), cookersPool);
	}
	GETCMP2(cookersPool, CookerPool)->addCooker(c);
	timers_.push_back(c->getCookerTimer());
}

void CookersAdder::initializeComponent(const string& component, Entity* entity) {
	switch (str2int(component.c_str()))
	{
	case str2int("loquesea"):
		break;
	default:
		break;
	}
}