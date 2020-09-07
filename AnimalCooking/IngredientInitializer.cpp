#include "IngredientInitializer.h"
#include "Ingredient.h"

#define MAKE(t) makeIngredient<t>(type, n)

IngredientInitializer::IngredientInitializer(jute::jValue& jsonLevel, GameControl* gc)
{
	//Se a�aden las ingredientes del nivel actual en el GameControl
	jute::jValue ingsType = jsonLevel["IngredientsPool"]["entities"];
	for (int i = 0; i < ingsType.size(); ++i)
	{
		jute::jValue ingType = jsonLevel["IngredientsPool"]["entities"][i];
		gc->getLevelIngType().push_back(newIngType(ingType.as_string()));
	}
}


constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

Resources::IngredientType IngredientInitializer::newIngType(const string& s) {

	Resources::IngredientType i = Resources::IngredientType::carrot;

	switch (str2int(s.c_str()))
	{
	case str2int("Tomato"):
		i = Resources::IngredientType::tomato;
		break;
	case str2int("Carrot"):
		i = Resources::IngredientType::carrot;
		break;
	case str2int("Lettuce"):
		i = Resources::IngredientType::lettuce;
		break;
	case str2int("Mushroom"):
		i = Resources::IngredientType::mushroom;
		break;
	case str2int("Sausage"):
		i = Resources::IngredientType::sausage;
		break;
	case str2int("Chicken"):
		i = Resources::IngredientType::chicken;
		break;
	case str2int("Meat"):
		i = Resources::IngredientType::meat;
		break;
	case str2int("Potato"):
		i = Resources::IngredientType::potato;
		break;
	case str2int("Onion"):
		i = Resources::IngredientType::onion;
		break;
	case str2int("Clam"):
		i = Resources::IngredientType::clam;
		break;
	case str2int("Cheese"):
		i = Resources::IngredientType::cheese;
		break;
	case str2int("Fish"):
		i = Resources::IngredientType::fish;
		break;
	case str2int("Snowman"):
		i = Resources::IngredientType::snowman;
		break;
	case str2int("Avocado"):
		i = Resources::IngredientType::avocado;
		break;
	case str2int("Salmon"):
		i = Resources::IngredientType::salmon;
		break;
	default:
		break;
	}
	return i;
}