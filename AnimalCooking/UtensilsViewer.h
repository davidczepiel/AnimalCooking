#pragma once
#include "Component.h"
#include "UtensilsPool.h"
#include "Utensil.h"

class UtensilsViewer : public Component
{
private:
	vector<Utensil*>* pool_;

public:
	UtensilsViewer() : Component(ecs::UtensilsViewer) { }
	virtual ~UtensilsViewer() { }
	void init() override;
	void draw() override;
};

