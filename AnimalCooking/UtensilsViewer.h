#pragma once
#include "Component.h"
#include "UtensilsPool.h"
#include "Utensil.h"

class UtensilsViewer : public Component
{
public:
	UtensilsViewer() : Component(ecs::UtensilsViewer),pool_() { }
	virtual ~UtensilsViewer() { }

	void init() override;
	void draw() override;
private:
	vector<Utensil*>* pool_;
};

