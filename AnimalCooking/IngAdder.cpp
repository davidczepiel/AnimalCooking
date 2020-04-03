#include "IngAdder.h"
#include "Ingredient.h"
#include "IngredientsPool.h"

#define MAKE(t) makeIngredient<t>(type, n)

IngAdder::IngAdder(Entity* ing, jute::jValue& jsonLevel, jute::jValue& jsonGeneral) :
	ingPoolEntity_(ing), jsonLevel(jsonLevel), jsonGeneral(jsonGeneral)
{
	jute::jValue ingsType = jsonLevel["IngredientsPool"]["entities"];

	for (int i = 0; i < ingsType.size(); ++i) {
		jute::jValue ings = jsonLevel["IngredientsPool"]["entities"][i];
		for (int j = 0; j < ings.size(); ++j) {
			switchIng(jsonLevel["IngredientsPool"]["entities"][i][j].as_string(), i, j);
		}
	}
}

template <typename T>
void IngAdder::makeIngredient(int type, int n)
{
	Ingredient* i = new T();
	i->setSize(128, 128);
	i->setVel(Vector2D(0, 0));
	i->setPos(Vector2D(jsonLevel["IngredientsPool"]["entities"][type][n]["pos"]["x"].as_int(), jsonLevel["IngredientsPool"]["entities"][type][n]["pos"]["y"].as_int()));
	GETCMP2(ingPoolEntity_, IngredientsPool)->addIngredient(i);
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}


void IngAdder::switchIng(const string& ing, int type, int n)
{
	switch (str2int(ing.c_str()))
	{
	case str2int("Tomato"):
		MAKE(Tomato);
		break;
	default:
		break;
	}
}