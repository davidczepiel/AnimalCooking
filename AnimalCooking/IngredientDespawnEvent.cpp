#include "IngredientDespawnEvent.h"

IngredientDespawnEvent::IngredientDespawnEvent()
{
	setEventId(6);
	setItemType(itemType::Ingredient);
}

IngredientDespawnEvent::~IngredientDespawnEvent()
{
}
