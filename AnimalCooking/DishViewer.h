#pragma once
#include "Component.h"
#include "DishPool.h"
#include "Texture.h"
#include "Entity.h"
#include "Transform.h"
#include "SDL_macros.h"
#include <list>

class DishViewer : public Component
{
public:
	DishViewer();
	virtual ~DishViewer() { }
	void draw()override;
	void init() override;


private:
	Texture* dish = nullptr; //textura plato vacio
	DishPool* dp = nullptr;
};

