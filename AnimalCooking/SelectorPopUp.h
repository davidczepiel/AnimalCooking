#pragma once
#include "Component.h"
#include "Interactive.h"
template<typename T>
class SelectorPopUp : public Component
{
public:
	SelectorPopUp(T<Interactive>& k):Component(ecs::SelectorPopUp)
private:
};

