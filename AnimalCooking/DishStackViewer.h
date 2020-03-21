#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"

class DishStackViewer : public Component	
{
public:
	DishStackViewer();
	~DishStackViewer() { }
	void init()override;
	void draw() override;

private:
	Texture* stack = nullptr;
	Transform* trDishStack = nullptr;
};

