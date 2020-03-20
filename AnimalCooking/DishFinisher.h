#pragma once
#include "Component.h"
#include "Transport.h"
#include "Dish.h"

class DishFinisher : public Component {
public:
	DishFinisher(Transport* tr);
	~DishFinisher();
	void finish();

private:
	Transport* tr_;
};