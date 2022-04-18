#pragma once
#include "GameEvent.h"

class IngredientKillEvent : public GameEvent {
public:
	IngredientKillEvent();
	~IngredientKillEvent();
	virtual std::string toJson() override;
	
	inline bool getMistake() const {
		return _mistake;
	}

	inline IngredientKillEvent* setMistake(bool m) {
		_mistake = m;
		return this;
	}
	inline IngredientKillEvent* setIngredient(size_t i) {
		_ingredient = i;
		return this;
	}

private:
	bool _mistake;
	size_t _ingredient;
};

