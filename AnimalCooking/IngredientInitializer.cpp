#include "IngredientInitializer.h"
#include "Ingredient.h"

#define MAKE(t) makeIngredient<t>(type, n)

IngredientInitializer::IngredientInitializer(jute::jValue& jsonLevel, GameControl* gc): jsonLevel(jsonLevel)
{
	//Se a�aden las ingredientes del nivel actual en el GameControl
	jute::jValue ingsType = jsonLevel["IngredientsPool"]["entities"];
	for (int i = 0; i < ingsType.size(); ++i) {
		jute::jValue ings = jsonLevel["IngredientsPool"]["entities"][i][0];
		
		gc->getLevelIngType().push_back(ings.as_string());
	}
}
