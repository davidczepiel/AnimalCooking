#pragma once
#include "GameEvent.h"

class IngredientDespawnEvent : public GameEvent {
public:
	IngredientDespawnEvent();
	~IngredientDespawnEvent();

	virtual std::string toJson() override;

	inline IngredientDespawnEvent* setIngredient(size_t i) {
		_ingredient = i;
		return this;
	}
private:
	size_t _ingredient;
};

