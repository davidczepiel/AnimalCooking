#pragma once
#include "Food.h"
class provisional1 :
	public Food
{
public:
	provisional1() { cout << "provisional1"; }
	virtual void draw(){}
private:
	provisional1* d = nullptr;
};

