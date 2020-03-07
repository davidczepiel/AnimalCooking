#pragma once
#include "Component.h"
#include "Food.h"
#include "ObjectPool.h"

class InOutFood : public Component
{
 public:
	InOutFood();
	~InOutFood() { }
	void addFood(Food* f);
	void takeFood(Food* f);
	vector<Food*>* getPool();
	inline void setEmpty(bool b);
	inline bool isEmpty();
	
 private:

	 bool empty = true;
	 vector<Food*> foods_;
};

