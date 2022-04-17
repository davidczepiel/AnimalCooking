#include "IngredientKillEvent.h"

IngredientKillEvent::IngredientKillEvent(): _mistake(false)
{
	setEventId(7);
	setItemType(itemType::Ingredient);
}

IngredientKillEvent::~IngredientKillEvent()
{
}

std::string IngredientKillEvent::toJson()
{
	if(_mistake)
		return AnimalCookingEvent::toJson() + ",\"mistake\":true";
	return AnimalCookingEvent::toJson()  + ",\"mistake\":false";
}

bool IngredientKillEvent::getMistake() const
{
	return _mistake;
}

void IngredientKillEvent::setMistake(bool m)
{
	_mistake = m;
}
