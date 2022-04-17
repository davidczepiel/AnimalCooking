//#include "pch.h"
#include "AnimalCookingEvent.h"

AnimalCookingEvent::AnimalCookingEvent(): _itemType(itemType::Undefined), _itemId(0)
{

}

AnimalCookingEvent::~AnimalCookingEvent()
{
}

std::string AnimalCookingEvent::toJson()
{
	std::string itemJson;
	switch (_itemType)
	{	
		case itemType::Dish: itemJson = ",\"dish\":";	break;
		case itemType::Ingredient: itemJson = ",\"ingredient\":";	break;
		case itemType::Utensil: itemJson = ",\"utensil\":";	break;	
		default: itemJson = ",\"undefined\":";	break;
	}
	return GameEvent::toJson() + itemJson + std::to_string(_itemId);
}


void AnimalCookingEvent::setItemId(const uint16_t iI)
{
	_itemId = iI;
}


uint16_t AnimalCookingEvent::getItemId() const
{
	return _itemId;
}

void AnimalCookingEvent::setItemType(const itemType iT)
{
	_itemType = iT;
}