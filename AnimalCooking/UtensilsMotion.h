#pragma once
#include "Component.h"
#include "Utensil.h"
#include "UtensilsPool.h"

class UtensilsMotion :
	public Component
{
private:
	vector<Utensil*> pool_;

public:
	UtensilsMotion() : Component(ecs::UtensilsMotion) { }
	virtual ~UtensilsMotion() { }
	void init() override;
	void update() override;
};

