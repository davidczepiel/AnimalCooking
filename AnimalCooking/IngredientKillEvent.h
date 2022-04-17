#pragma once
#include "AnimalCookingEvent.h"

class IngredientKillEvent : public AnimalCookingEvent {
public:
	IngredientKillEvent();
	~IngredientKillEvent();
	virtual std::string toJson() override;
	
	bool getMistake() const;

	void setMistake(bool m);
private:
	bool _mistake;
};

