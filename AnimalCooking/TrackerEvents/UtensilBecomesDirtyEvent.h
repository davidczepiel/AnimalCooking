#pragma once
#include "GameEvent.h"

class UtensilBecomesDirtyEvent : public GameEvent {
public:
	UtensilBecomesDirtyEvent();
	~UtensilBecomesDirtyEvent();

	inline UtensilBecomesDirtyEvent* setUtensil(size_t utensil) {
		_utensil = utensil;
		return this;
	}
	virtual std::string toJson() override;
private:

	size_t _utensil;
};

