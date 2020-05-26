#pragma once
#include "Component.h"
#include "Transport.h"
#include "Dish.h"

class DishFinisher : public Component {
public:
	DishFinisher(Transport* tr1, Transport* tr2);
	~DishFinisher();
	void finish(int id, Dish* d);

private:
	Transport* tr1_;
	Transport* tr2_;

};