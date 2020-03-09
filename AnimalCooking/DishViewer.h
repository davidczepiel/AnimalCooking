#pragma once
#include "Component.h"
#include "Texture.h"
#include <list>

class DishViewer : public Component
{
public:
	DishViewer();
	virtual ~DishViewer() { }
	void draw()override;


private:
	Texture* dish = nullptr; //textura plato vacio
	
};

