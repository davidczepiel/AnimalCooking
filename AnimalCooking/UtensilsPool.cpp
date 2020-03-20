#include "UtensilsPool.h"

UtensilsPool::UtensilsPool(size_t size) : Component(ecs::UtensilsPool)
{
    pool_.reserve(size);
}

UtensilsPool::~UtensilsPool() {
	for (Utensil* u : pool_) {
		delete u;
	}
}


