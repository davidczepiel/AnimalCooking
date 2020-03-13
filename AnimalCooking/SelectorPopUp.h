#pragma once
#include "Component.h"
#include "Interactive.h"
#include "Transform.h"
#include "Selector.h"
#include "Collisions.h"

class SelectorPopUp : public Component
{
public:
	//p: pool de los interactivos
	//tr1, tr2: transform de los players
	SelectorPopUp(vector<Interactive*> p, Transform* tr1, Transform* tr2, Selector* sl1, Selector* sl2) :
				Component(ecs::SelectorPopUp), pool_(p), tr1_(tr1), tr2_(tr2), sl1_(sl1),sl2_(sl2){}
	~SelectorPopUp();
	
	void update() override;
private:
	vector<Interactive*> pool_;
	Transform* tr1_ = nullptr;
	Transform* tr2_ = nullptr;
	Selector* sl1_ = nullptr;
	Selector* sl2_ = nullptr;
};

