#pragma once
#include "Component.h"
class Selector : public Component
{
public:
	Selector() :Component(ecs::Selector) {};
	~Selector() {};
};

