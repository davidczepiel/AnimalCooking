#include "FoodViewer.h"
#include "FoodPool.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Food.h"

void FoodViewer::draw()
{
	std::vector<Food*> fp = foodPool_->getPool();
	for (Food* f : fp) {
		if (f->getInUse()) {
			f->draw();
		}
	}
}

void FoodViewer::init()
{
	foodPool_ = GETCMP1_(FoodPool);
}
