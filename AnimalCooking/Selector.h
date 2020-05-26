#pragma once
#include "Component.h"
#include "Interactive.h"
#include "Collisions.h"
#include "InteractionRect.h"
#include "Entity.h"
#include "Transform.h"

using namespace std;

class Selector : public Component
{
public:
	Selector() :Component(ecs::Selector) {};
	~Selector() {};
	inline Interactive* getSelect() { return select_; }
	inline void setSelect(Interactive* i, int area) { select_ = i; interationArea = area; }
	inline int getInteractionArea() { return interationArea; }

	void update() override;
private:
	Interactive* select_ = nullptr;
	int interationArea;
};

