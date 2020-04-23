#pragma once
#include "Component.h"
#include "Transform.h"
#include <array>
#include "Entity.h"

enum State : size_t {
	Closed,
	OpenedLeft,
	OpenedRight
};

class DoorRenderer : public Component
{
public:
	DoorRenderer(Transform* tr, Transform* p1, Transform* p2, Texture* texture);
	void update() override;
	void draw() override;
private:
	State checkCollision();
	State state;
	double animState;
	Transform* tr;
	Texture* t;
	std::array<Transform*, 2> players;
};

