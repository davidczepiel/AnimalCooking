#include "UtensilCleanEvent.h"

UtensilCleanEvent::UtensilCleanEvent() : GameEvent()
{
	_myType = "UtensilCleanEvent";
}

UtensilCleanEvent::~UtensilCleanEvent()
{
}

std::string UtensilCleanEvent::toJson()
{
	return GameEvent::toJson() + ",\"_ingredient\":" + std::to_string(_utensil) +  "},";
}
