#include "IngredientKillEvent.h"

IngredientKillEvent::IngredientKillEvent(): GameEvent(), _mistake(false)
{
	_myType = "IngredientKillEvent";
}

IngredientKillEvent::~IngredientKillEvent()
{
}

std::string IngredientKillEvent::toJson()
{
	if(_mistake)
		return GameEvent::toJson() + ",\"mistake\":true, \"_ingredient\":" + std::to_string(_ingredient) + "},";
	return GameEvent::toJson()  + ",\"mistake\":false, \"_ingredient\":" + std::to_string(_ingredient) + "},";
}

