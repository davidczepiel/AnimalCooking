#pragma once
#include "Component.h"
#include "Selector.h"
class FeedBack : public Component
{
public:
	FeedBack(Selector* s1, Selector* s2) : Component(ecs::FeedBack), s1_(s1), s2_(s2) {}
	~FeedBack() {}

	void draw() override;
private:
	Selector* s1_;
	Selector* s2_;
};

