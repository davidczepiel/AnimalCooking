#pragma once
#include "GameEvent.h"

class UtensilCleanEvent : public GameEvent {
public:
	UtensilCleanEvent();
	~UtensilCleanEvent();

	inline UtensilCleanEvent* setUtensil(size_t utensil) {
		_utensil = utensil;
		return this;
	}

	virtual std::string toJson() override;
private:
	size_t _utensil;
	
};

