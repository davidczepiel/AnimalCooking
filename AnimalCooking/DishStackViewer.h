#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"
#include "Interactive.h"

class DishStackViewer : public Component
{
public:
	DishStackViewer(Interactive* i);
	~DishStackViewer() {}

	void init()override;
	void draw() override;

private:
	Texture* stack = nullptr;
	Interactive* entity = nullptr;
};

