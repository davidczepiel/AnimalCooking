#pragma once
#include "Component.h"
#include "Interactive.h"
class Selector : public Component
{
public:
	Selector() :Component(ecs::Selector) {};
	~Selector() {};
	inline Interactive* getSelect() { return select_; }
	inline void setSelect(Interactive* i) { select_ = i; }
private:
	Interactive* select_ = nullptr;
};

