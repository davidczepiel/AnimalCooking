#pragma once
#include "Component.h"
#include "Transform.h"
#include "Physics.h"
class PlayerMotion : public Component {
public:
	PlayerMotion() : Component(ecs::PlayerMotion) {};
	void init() override;
	void update() override;
private:
	Transform* tr_ = nullptr;
	Physics* ph = nullptr;
	const double SPEED = 5.3;
};

