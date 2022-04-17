#pragma once
#include "AnimalCookingEvent.h"

class DishFinishedEvent : public AnimalCookingEvent {
public:
	DishFinishedEvent();
	~DishFinishedEvent();
	virtual std::string toJson() override;

	bool getResult() const;

	void setResult(bool m);
private:
	bool _result;
};

