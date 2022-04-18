#include "IngredientDespawnEvent.h"

IngredientDespawnEvent::IngredientDespawnEvent() : GameEvent()
{
	_myType = "IngredientDespawnEvent";
}

IngredientDespawnEvent::~IngredientDespawnEvent()
{
}

std::string IngredientDespawnEvent::toJson()
{
	return GameEvent::toJson() + ",\"_ingredient\":" + std::to_string(_ingredient) +  "},";
}
