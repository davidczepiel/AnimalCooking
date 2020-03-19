#pragma once
#include "Component.h"
#include "Transform.h"
#include "Pickable.h"

class Transport : public Component {
public:
	Transport();

	void pick(Pickable* obj, Resources::PickableType objType);
	void drop();

	void init() override;
	void update() override;

	Pickable* getObjectInHands() { return objInHands_; }
	
	bool hasEmptyDish();
	bool hasDish() { return objType_ == Resources::PickableType::Dish; }

private:
	Pickable* objInHands_;
	Transform* playerTransform_;
	Resources::PickableType objType_;

	void swap(Pickable* obj, Resources::PickableType objType);
};