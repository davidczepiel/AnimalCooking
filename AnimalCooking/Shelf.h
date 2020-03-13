#pragma once
#include "Component.h"
class Shelf :
	public Component
{

public:
	//Pickable* content
	bool Deposit();
	void Pick();
};

