#pragma once
#include "GameEvent.h"

class AnimalCookingEvent: public GameEvent {
public:
	AnimalCookingEvent();
	~AnimalCookingEvent();

	virtual std::string toJson();

protected:
	std::string _myType;
};

