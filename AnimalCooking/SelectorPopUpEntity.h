#pragma once
#include "Component.h"
#include "InteractionRect.h"
#include "Selector.h"
#include "Collisions.h"
#include "Interactive.h"

class SelectorPopUpEntity :	public Component
{
public:	
	SelectorPopUpEntity(InteractionRect* it1, InteractionRect* it2, Selector* sl1, Selector* sl2, Interactive* proper) :
		Component(ecs::SelectorPopUpEntity), it1_(it1), it2_(it2), sl1_(sl1), sl2_(sl2), proper(proper) {}
	~SelectorPopUpEntity() {}

	void update() override;
private:
	InteractionRect* it1_ = nullptr;
	InteractionRect* it2_ = nullptr;
	Selector* sl1_ = nullptr;
	Selector* sl2_ = nullptr;
	Interactive* proper;

};

