#include "UtensilBecomesDirtyEvent.h"

UtensilBecomesDirtyEvent::UtensilBecomesDirtyEvent() : GameEvent()
{
	_myType = "UtensilBecomesDirtyEvent";
}

UtensilBecomesDirtyEvent::~UtensilBecomesDirtyEvent()
{
}

std::string UtensilBecomesDirtyEvent::toJson()
{
	return GameEvent::toJson() + ",\"_ingredient\":" + std::to_string(_utensil) + "},";
}
