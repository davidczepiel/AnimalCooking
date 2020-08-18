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
	std::vector<Food*> fp = foodPool_->getPool();
	for (auto& f : fp) {
		if (f->getCanDraw())
			f->draw();
		
	}
}

void FoodViewer::init()
{
	foodPool_ = GETCMP1_(FoodPool);
}
