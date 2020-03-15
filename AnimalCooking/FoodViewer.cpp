#include "FoodViewer.h"
#include "FoodPool.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Food.h"

FoodViewer::FoodViewer() : Component(ecs::FoodViewer) {
	foodPool_ = nullptr;
}

void FoodViewer::draw()
{
	std::vector<Food*>* fp = foodPool_->getPool();
	Food* aux;
	for (int i = 0; i < fp->size(); ++i) {
		aux = fp->at(i);
		aux->draw();
	}
}

void FoodViewer::init()
{
	foodPool_ = GETCMP1_(FoodPool);
}
