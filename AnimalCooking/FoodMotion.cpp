#include "FoodPool.h"
#include "FoodMotion.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Food.h"

void FoodMotion::update()
{
	std::vector<Food*> fp = foodPool_->getPool();
	for (Food* f : fp) {
		if (f->getInUse()) {
			f->update();
		}
	}
}

void FoodMotion::init()
{
	foodPool_ = GETCMP1_(FoodPool);
}
