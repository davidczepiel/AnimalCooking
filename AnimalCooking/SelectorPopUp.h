#pragma once
#include "Component.h"
#include "Interactive.h"
#include "InteractionRect.h"
#include "Selector.h"
#include "Collisions.h"

class SelectorPopUp : public Component
{
public:
	//p: pool de los interactivos
	//tr1, tr2: transform de los players
	SelectorPopUp(vector<Interactive*>* p, InteractionRect* it1, InteractionRect* it2, Selector* sl1, Selector* sl2) :
				Component(ecs::SelectorPopUp), pool_(p), it1_(it1), it2_(it2), sl1_(sl1),sl2_(sl2){}
	~SelectorPopUp();
	
	void update() override;
private:
	vector<Interactive*>* pool_;
	InteractionRect* it1_ = nullptr;
	InteractionRect* it2_ = nullptr;
	Selector* sl1_ = nullptr;
	Selector* sl2_ = nullptr;
};

