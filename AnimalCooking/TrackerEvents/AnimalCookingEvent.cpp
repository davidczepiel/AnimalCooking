#include "pch.h"
#include "AnimalCookingEvent.h"

AnimalCookingEvent::AnimalCookingEvent(): GameEvent()
{

}

AnimalCookingEvent::~AnimalCookingEvent()
{
}

std::string AnimalCookingEvent::toJson()
{
	return TrackerEvent::toJson() + ",\"_myType\": " +  "\"" +_myType + "\"";
}

