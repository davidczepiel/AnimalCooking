#pragma once
#include "Component.h"
#include "Utensil.h"
#include "UtensilsPool.h"

class UtensilsMotion : public Component	
{

public:
	UtensilsMotion() : Component(ecs::UtensilsMotion),pool_() {}
	~UtensilsMotion() {}

	void init() override;
	void update() override;
private:
	vector<Utensil*>* pool_;
};

