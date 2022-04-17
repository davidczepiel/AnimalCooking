#pragma once
#include "AnimalCookingEvent.h"

class UtensilBecomesDirtyEvent : public AnimalCookingEvent {
public:
	UtensilBecomesDirtyEvent();
	~UtensilBecomesDirtyEvent();
private:
};

