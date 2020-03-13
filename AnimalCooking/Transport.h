#pragma once
#include "Component.h"
#include "Transform.h"
#include "Pickable.h"

class Transport : public Component {
public:
	Transport();

	void pick(Pickable* obj);
	void drop();

	void init() override;
	void update() override;

private:
	Pickable* objInHands_;
	Transform* playerTransform_;

	void swap(Pickable* obj);
};