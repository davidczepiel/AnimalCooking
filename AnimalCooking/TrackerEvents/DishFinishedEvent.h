#pragma once
#include "GameEvent.h"
#include "../Resources.h"

class DishFinishedEvent : public GameEvent {
public:
	DishFinishedEvent();
	~DishFinishedEvent();
	virtual std::string toJson() override;

	bool getResult() const { return _result; };

	DishFinishedEvent* setResult(bool m) {
		_result = m;
		return this;
	}

	DishFinishedEvent* setDish(size_t d) {
		_dish = d;
		return this;
	}
private:
	bool _result;
	size_t _dish;
	
};

