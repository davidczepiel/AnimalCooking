#include "DishFinishedEvent.h"

DishFinishedEvent::DishFinishedEvent() : _result(false)
{
	setEventId(5);
	setItemType(itemType::Dish);
}

DishFinishedEvent::~DishFinishedEvent()
{
}

std::string DishFinishedEvent::toJson()
{
	if (_result)
		return GameEvent::toJson() + ",\"result\": true";
	return GameEvent::toJson() + ",\"result\": false";
}

bool DishFinishedEvent::getResult() const
{
	return false;
}

void DishFinishedEvent::setResult(bool m)
{
}
