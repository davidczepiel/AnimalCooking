#pragma once
#include "Component.h"
#include "Transform.h"
#include "Pickable.h"

class Transport : public Component {
public:
	Transport();

	void pick(Pickable* obj, Resources::PickableType objType, bool inFloor = true);
	void drop(bool onFloor = true);

	void init() override;
	void update() override;

	Pickable* getObjectInHands() { return objInHands_; }
	Resources::PickableType getObjectTypeInHands() { return objType_; }
	void setObjectInHands(Pickable* p) { objInHands_ = p; }
	void setObjectTypeInHands(Resources::PickableType p) { objType_ = p; }
	void setDir(Vector2D v) { dir = v; }

private:
	Pickable* objInHands_;
	Transform* playerTransform_;
	Resources::PickableType objType_;
	Vector2D dir;
	void swap(Pickable* obj, Resources::PickableType objType, bool inFloor = true);
};