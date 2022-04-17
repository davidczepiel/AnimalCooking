#pragma once
#include "GameEvent.h"

class AnimalCookingEvent: public GameEvent {
public:
	AnimalCookingEvent();
	~AnimalCookingEvent();
	virtual std::string toJson();

	void setItemId(const uint16_t iI);
	uint16_t getItemId() const;

protected:
	enum itemType { Dish, Ingredient, Utensil, Undefined };
	void setItemType(const itemType iT);
	itemType _itemType;
	uint16_t _itemId;
};

