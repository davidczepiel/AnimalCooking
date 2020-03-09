#pragma once

#include "Component.h"
#include "IngredientsPool.h"

class IngredientViewer : public Component
{
private:
	IngredientsPool* pool_;
public:
	IngredientViewer() : Component(ecs::IngredientViewer), pool_(nullptr) {}
	virtual ~IngredientViewer() { }
	void init() override;
	void draw() override;
};