#include "UtensilsPool.h"

UtensilsPool::UtensilsPool() : Component(ecs::UtensilsPool)
{
	//Se podría meter en un orden concreto para que al preparar los niveles siempre estén ordenados en las repisas
	//porque al empezar se hace disableall y al hacer getObj te los da en ese orden concreto
		Knife* t = new Knife(Vector2D(1,1),nullptr, nullptr);
		pool_.push_back(t);
		Mace* m = new Mace(Vector2D(1, 1), nullptr, nullptr);
		pool_.push_back(m);
		Grater* g = new Grater(Vector2D(1, 1), nullptr, nullptr);
		pool_.push_back(g);
		Net* n = new Net(Vector2D(1, 1), nullptr, nullptr);
		pool_.push_back(n);
}


