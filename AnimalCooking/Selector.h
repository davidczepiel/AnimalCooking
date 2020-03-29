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
	inline void setSelect(Interactive* i) { select_ = i;	cout << "interactive2" << endl; }

	void update() override;
private:
	Interactive* select_ = nullptr;
};

