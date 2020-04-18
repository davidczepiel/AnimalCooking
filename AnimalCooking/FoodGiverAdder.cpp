#include "FoodGiverAdder.h"
#define ADD(T) fg = makeFoodGiver<T>(type,n)
#define CASTID(t) static_cast<ecs::GroupID>(t - 1)

FoodGiverAdder::FoodGiverAdder(EntityManager* mngr, jute::jValue nivel, jute::jValue general, std::array<Entity*, 2>& player, Entity* gameManager, const double casilla)
	:mngr(mngr), nivel(nivel), general(general), casilla(casilla), players(player), gameManager(gameManager)
{
	jute::jValue ents = nivel["FoodGivers"];
	for (size_t i = 0; i < ents.size(); i++)
	{
		for (size_t n = 0; n < ents[i][1].size(); n++)
		{
			FoodGiver* fg = SwitchFG(ents[i][0].as_string(), i, n);
			for (int c = 0; c < ents[i][1]["components"].size(); ++c) {
				initializeComponent(ents[i][1]["components"][c].as_string(), fg);
			}
		}
	}
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
FoodGiver* FoodGiverAdder::SwitchFG(const string& fgName, int type, int n) {
	FoodGiver* fg = nullptr;
	switch (str2int(fgName.c_str()))
	{
	case str2int("BreadGiver"):
		ADD(BreadGiver);
		break;
	case str2int("DressingGiver"):
		ADD(DressingGiver);
		break;
	case str2int("RiceGiver"):
		ADD(RiceGiver);
		break;
	default:
		break;
	}
	return fg;
}
template <typename T>
FoodGiver* FoodGiverAdder::makeFoodGiver(int type, int n)
{
	FoodGiver* fg = new T(Vector2D(nivel["FoodGivers"][type][1][n]["pos"]["x"].as_double() * casilla, nivel["FoodGivers"][type][1][n]["pos"]["y"].as_double() * casilla),
		Vector2D(general["Givers"]["size"]["width"].as_double() * casilla, general["Givers"]["size"]["height"].as_double() * casilla),
		GETCMP2(players[0], Transport), GETCMP2(players[1], Transport), GETCMP2(gameManager, GameControl));
	fg->addComponent<FoodGiverViewer>(fg);
	fg->addComponent<SelectorPopUpEntity>(GETCMP2(players[0], InteractionRect), GETCMP2(players[1], InteractionRect),
		GETCMP2(players[0], Selector), GETCMP2(players[1], Selector), fg);

	mngr->addEntity(fg);
	mngr->addToGroup(fg, CASTID(general["Givers"]["Layer"].as_int()));
	interactives_.push_back(fg);
	return fg;
}
//La cadena (component) no puede superar 10 caracteres
void FoodGiverAdder::initializeComponent(const string& component, Entity* entity)
{
	switch (str2int(component.c_str()))
	{
	case str2int("AdvEffect"):
		break;
	default:
		break;
	}
}