#pragma once
#include "Food.h"
class Provisional2 :
	public Food
{
public:
	Provisional2() { cout << "2"; }
	virtual void draw(){}
private:
 Provisional2* d = nullptr;
};

