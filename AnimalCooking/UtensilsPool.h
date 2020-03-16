#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Utensil.h"
class UtensilsPool: public Component
{
public:
	UtensilsPool();
	~UtensilsPool() {}

	void init() override {};
	void update() override {};
	void draw() override {};
	Utensil* getKnife() { return getPool().at(0);}
	Utensil* getMace() { return getPool().at(1); }
	Utensil* getGrater() { return getPool().at(2); }
	Utensil* getNet() { return getPool().at(3); }
	
	inline std::vector<Utensil*> getPool() { return pool_; }
private:
	vector<Utensil*> pool_;
};

