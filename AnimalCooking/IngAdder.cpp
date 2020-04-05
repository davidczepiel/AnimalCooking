#include "IngAdder.h"
#include "Ingredient.h"
#include "IngredientsPool.h"
#include "LevelInitializer.h"
#include "IngredientViewer.h"
#include "IngredientMotion.h"

#define MAKE(t) makeIngredient<t>(type, n)

IngAdder::IngAdder(Entity* ing, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, const double casillaLength) :
	ingPoolEntity_(ing), jsonLevel(jsonLevel), jsonGeneral(jsonGeneral), casillaLength(casillaLength)
{
	ingPoolEntity_->addComponent<IngredientsPool>();
	ingPoolEntity_->addComponent<IngredientViewer>();
	ingPoolEntity_->addComponent<IngredientMotion>();

	jute::jValue ingsType = jsonLevel["IngredientsPool"]["entities"];

	for (int i = 0; i < ingsType.size(); ++i) {
		jute::jValue ings = jsonLevel["IngredientsPool"]["entities"][i][1];
		for (int j = 0; j < ings.size(); ++j) {
			switchIng(jsonLevel["IngredientsPool"]["entities"][i][0].as_string(), i, j);
		}
	}

	jute::jValue components = jsonLevel["IngredientsPool"]["components"];
	if (components.size() > 0) { //Si tiene algun componente extra en ese nivel
		for (int c = 0; c < components.size(); ++c) {
			initializeComponent(components[c].as_string(), ingPoolEntity_);
		}
	}
}

template <typename T>
void IngAdder::makeIngredient(int type, int n)
{
	Ingredient* i = new T();
	i->setSize(jsonGeneral["Ingredientes"]["size"]["width"].as_double() * casillaLength,
			   jsonGeneral["Ingredientes"]["size"]["height"].as_double() * casillaLength);
	i->setVel(Vector2D(0, 0));
	i->setPos(Vector2D(jsonLevel["IngredientsPool"]["entities"][type][1][n]["pos"]["x"].as_double() * casillaLength,
					   jsonLevel["IngredientsPool"]["entities"][type][1][n]["pos"]["y"].as_double() * casillaLength));
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
	case str2int("Carrot"):
		MAKE(Carrot);
		break;
	case str2int("Lettuce"):
		MAKE(Lettuce);
		break;
	case str2int("Mushroom"):
		MAKE(Mushroom);
		break;
	case str2int("Sausage"):
		MAKE(Sausage);
		break;
	case str2int("Chicken"):
		MAKE(Chicken);
		break;
	case str2int("Meat"):
		MAKE(Meat);
		break;
	case str2int("Potato"):
		MAKE(Potato);
		break;
	case str2int("Onion"):
		MAKE(Onion);
		break;
	case str2int("Clam"):
		MAKE(Clam);
		break;
	case str2int("Cheese"):
		MAKE(Cheese);
		break;
	case str2int("Fish"):
		MAKE(Fish);
		break;
	default:
		break;
	}
}

//La cadena (component) no puede superar 10 caracteres
void IngAdder::initializeComponent(const string& component, Entity* entity)
{
	switch (str2int(component.c_str()))
	{
	case str2int("AdvEffect"):
		break;
	default:
		break;
	}
}