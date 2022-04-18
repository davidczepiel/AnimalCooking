#pragma once
#include "GameEvent.h"
#include "../Resources.h"

class DirtyUtensilsAttackEvent : public GameEvent {
public:
	DirtyUtensilsAttackEvent();
	~DirtyUtensilsAttackEvent();

	inline DirtyUtensilsAttackEvent* setUtensil(size_t utensil) {
		_utensil = utensil;
		return this;
	}

	virtual std::string toJson();
private:
	size_t _utensil;
};

