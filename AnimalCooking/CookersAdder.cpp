#include "CookersAdder.h"
#include "CookerPool.h"
#define ADD(t)makeCooker<t>(type)

CookersAdder::CookersAdder(Entity* cookersPool, jute::jValue& jsonnivel, jute::jValue& jsongeneral, std::array<Entity*, 2> players, FoodPool* fp) :nivel(jsonnivel), general(jsongeneral), players(players), cookersPool(cookersPool)
{
	cookersPool->addComponent<CookerPool>();
	cookersPool->addComponent<FoodCooker>(fp);
	cookersPool->addComponent<CookerViewer>();
	cookersPool->addComponent<InsertExpel>(GETCMP2(players[0], Transport)/*players[1], Transport*/);
	jute::jValue cookerlist = jsonnivel["CookersPool"];
	for (size_t i = 0; i < cookerlist.size(); i++)
	{
		switchCookers(cookerlist[i].as_string(),i);
	}

}
constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
void CookersAdder::switchCookers(const string& cooker,int type) {
	switch (str2int(cooker.c_str()))
	{
	case str2int("Oven"):
		ADD(Oven);
		break;
	default:
		break;
	}
}
template<typename T>
void CookersAdder::makeCooker(int type) {
	Vector2D pos(nivel["CookersPool"][type]["pos"]["x"].as_int(), nivel["CookersPool"]["pos"]["y"].as_int());
	Vector2D size(general["Cookers"]["size"]["width"].as_int(), general["Cookers"]["size"]["height"].as_int());
	Cooker* c = new T(pos, size, general["Cookers"]["rotation"].as_int(), nullptr,
		GETCMP2(players[0], Transport), GETCMP2(players[1], Transport), cookersPool);
	for (size_t i = 0; i < nivel["CookersPool"][type]["components"]; i++)
	{
		initializeComponent(nivel["CookersPool"][type]["components"][i], cookersPool);
	}
	GETCMP2(cookersPool, CookerPool)->addCooker(c);


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