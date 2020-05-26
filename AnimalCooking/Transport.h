#pragma once
#include "Component.h"
#include "Transform.h"
#include "Pickable.h"
#include "InteractionRect.h"

class Transport : public Component {
public:
	Transport(InteractionRect* ir);

	void pick(Pickable* obj, Resources::PickableType objType, bool inFloor = true);
	void drop(bool onFloor = true);

	void init() override;
	void update() override;

	Pickable* getObjectInHands() { return objInHands_; }
	Resources::PickableType getObjectTypeInHands() { return objType_; }
	void setObjectInHands(Pickable* p) { objInHands_ = p; }
	void setObjectTypeInHands(Resources::PickableType p) { objType_ = p; }
	void setDir(const Vector2D& v) { dir = v; }

private:
	Pickable* objInHands_;
	Transform* playerTransform_;
	InteractionRect* interactionPlayerRect;
	Resources::PickableType objType_;
	Vector2D dir;
	void swap(Pickable* obj, Resources::PickableType objType, bool inFloor = true);
};