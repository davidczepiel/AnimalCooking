#include "UtensilsPool.h"

UtensilsPool::UtensilsPool() : Component(ecs::UtensilsPool)
{
	//Se podría meter en un orden concreto para que al preparar los niveles siempre estén ordenados en las repisas
	//porque al empezar se hace disableall y al hacer getObj te los da en ese orden concreto
		Knife* t = new Knife(Vector2D(1,1),nullptr);
		pool_.at(0) = t;
		Mace* m = new Mace(Vector2D(1, 1), nullptr);
		pool_.at(1) = m;
		Grater* g = new Grater(Vector2D(1, 1), nullptr);
		pool_.at(2) = g;
		Net* n = new Net(Vector2D(1, 1), nullptr);
		pool_.at(3) = n;
}


