#include "IngredientsPool.h"

IngredientsPool::IngredientsPool() : Component(ecs::IngredientsPool), pool_(30, [](Ingredient* i) {return i->inUse(); })
{
	for (int i = 0; i < 30; ++i) {	//30 tomates en la pool (testing)
		Tomato* t = new Tomato();
		pool_.getPool()[i] = t;
	}
	pool_.getPool()[10] = new Carrot();	//Zanahoria en la posicion 10 (testing)
}

///Añade un ingrediente del tipo indicado si quedan en la pool 
template<typename I>
void IngredientsPool::addIngredient(double w, double h, Vector2D pos, Vector2D vel)
{
	for(int e = 0; e < n; ++e){
		Ingredient* i = pool_.getObj<I>();
		if (i != nullptr) {
			i->setTransform(w, h, pos, vel);
			i->setInUse(true);
		}
	}
}

