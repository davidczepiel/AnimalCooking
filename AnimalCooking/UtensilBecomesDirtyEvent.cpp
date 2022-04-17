#include "UtensilBecomesDirtyEvent.h"

UtensilBecomesDirtyEvent::UtensilBecomesDirtyEvent()
{
	setEventId(8);
	setItemType(itemType::Utensil);
}

UtensilBecomesDirtyEvent::~UtensilBecomesDirtyEvent()
{
}
