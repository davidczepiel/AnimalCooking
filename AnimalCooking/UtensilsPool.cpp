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

void UtensilsPool::SetGameLogic(GameLogic* gl)
{
	for (int i = 0; i < pool_.size(); i++) {
		if (pool_.at(i) != nullptr) {
			pool_.at(i)->setGameLogic(gl);
		}
	}

}


