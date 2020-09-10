#pragma once
#include "Component.h"
#include "Transform.h"

class GhostLife : public Component
{
public:
	GhostLife();
	void init() override;
	void update() override;

	void restart();
private:
	Transform* tr;
	Uint32 startOfLife, lenghtOfLife;
};

